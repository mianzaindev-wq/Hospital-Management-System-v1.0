#ifndef MODULE_H
#define MODULE_H

#include <iostream>
#include <string>
#include <sstream>
#include <limits>
#include <regex>

using namespace std;

class InputTools {
private:
    // Helper function to trim whitespace from both ends of a string
    static string trim(const string& str) {
        if (str.empty()) return str;
        
        size_t start = 0;
        while (start < str.length() && (str[start] == ' ' || str[start] == '\t' || 
                                        str[start] == '\n' || str[start] == '\r')) {
            start++;
        }

        size_t end = str.length();
        while (end > start && (str[end - 1] == ' ' || str[end - 1] == '\t' || 
                               str[end - 1] == '\n' || str[end - 1] == '\r')) {
            end--;
        }

        return str.substr(start, end - start);
    }

    // Clear the input buffer in case of invalid input
    static void clearInputBuffer() {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

public:
    // Get validated integer input within a range
    static int getValidatedInteger(const string& prompt, int min = -2147483648, int max = 2147483647) {
        string input;
        while (true) {
            cout << "\n>> " << prompt;
            getline(cin, input);
            input = trim(input);

            if (input.empty()) {
                cout << "[ERROR] Input cannot be empty. Please enter a number.\n";
                continue;
            }

            bool valid = true;
            size_t i = (input[0] == '-') ? 1 : 0;

            // Check if string has at least one digit after the sign
            if (i >= input.length()) {
                cout << "[ERROR] Invalid number format.\n";
                continue;
            }

            for (; i < input.length(); ++i) {
                if (!isdigit(input[i])) {
                    valid = false;
                    break;
                }
            }

            if (!valid) {
                cout << "[ERROR] Invalid number. Please enter digits only.\n";
                continue;
            }

            try {
                // Use stoll for safer conversion and check for overflow
                long long temp = stoll(input);
                if (temp < min || temp > max) {
                    cout << "[ERROR] Number out of range (" << min << " - " << max << "). Please try again.\n";
                    continue;
                }
                return static_cast<int>(temp);
            } catch (const out_of_range&) {
                cout << "[ERROR] Number too large. Please try again.\n";
            } catch (...) {
                cout << "[ERROR] Conversion error. Try again.\n";
            }
        }
    }

    // Get validated non-empty string input
    static string getValidatedString(const string& prompt) {
        string input;
        while (true) {
            cout << "\n>> " << prompt;
            getline(cin, input);
            input = trim(input);
            if (!input.empty()) return input;
            cout << "[ERROR] Input cannot be empty. Please enter valid text.\n";
        }
    }

    // Get validated double input with minimum value
    static double getValidatedDouble(const string& prompt, double min = 0.0) {
        string input;
        while (true) {
            cout << "\n>> " << prompt;
            getline(cin, input);
            input = trim(input);

            if (input.empty()) {
                cout << "[ERROR] Input cannot be empty. Please enter a value.\n";
                continue;
            }

            bool valid = true;
            bool dotSeen = false;

            size_t i = (input[0] == '-') ? 1 : 0;

            // Check if there's at least one digit
            if (i >= input.length()) {
                cout << "[ERROR] Invalid number format.\n";
                continue;
            }

            for (; i < input.length(); ++i) {
                if (input[i] == '.') {
                    if (dotSeen) {
                        valid = false;
                        break;
                    }
                    dotSeen = true;
                } else if (!isdigit(input[i])) {
                    valid = false;
                    break;
                }
            }

            if (!valid) {
                cout << "[ERROR] Invalid number format. Only digits and one decimal point allowed.\n";
                continue;
            }

            try {
                double result = stod(input);
                if (result < min) {
                    cout << "[ERROR] Value must be at least " << min << ".\n";
                    continue;
                }
                return result;
            } catch (const out_of_range&) {
                cout << "[ERROR] Number too large. Please try again.\n";
            } catch (...) {
                cout << "[ERROR] Conversion error. Try again.\n";
            }
        }
    }

    // Get validated email input
    static string getValidatedEmail(const string& prompt) {
        string input;
        // Simple email regex pattern
        regex emailPattern(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
        
        while (true) {
            cout << "\n>> " << prompt;
            getline(cin, input);
            input = trim(input);

            if (input.empty()) {
                cout << "[ERROR] Email cannot be empty.\n";
                continue;
            }

            if (regex_match(input, emailPattern)) {
                return input;
            }

            cout << "[ERROR] Invalid email format. Please enter a valid email (e.g., user@example.com).\n";
        }
    }

    // Get validated phone number (flexible format)
    static string getValidatedPhone(const string& prompt) {
        string input;
        while (true) {
            cout << "\n>> " << prompt;
            getline(cin, input);
            input = trim(input);

            if (input.empty()) {
                cout << "[ERROR] Phone number cannot be empty.\n";
                continue;
            }

            // Remove common separators
            string cleaned;
            for (char c : input) {
                if (isdigit(c)) {
                    cleaned += c;
                } else if (c != '-' && c != ' ' && c != '(' && c != ')' && c != '+') {
                    cout << "[ERROR] Invalid characters in phone number.\n";
                    cleaned.clear();
                    break;
                }
            }

            if (!cleaned.empty() && cleaned.length() >= 10 && cleaned.length() <= 15) {
                return input; // Return original format
            }

            cout << "[ERROR] Phone number must contain 10-15 digits.\n";
        }
    }

    // Get validated date in YYYY-MM-DD format
    static string getValidatedDate(const string& prompt) {
        string input;
        regex datePattern(R"(\d{4}-\d{2}-\d{2})");
        
        while (true) {
            cout << "\n>> " << prompt;
            getline(cin, input);
            input = trim(input);

            if (input.empty()) {
                cout << "[ERROR] Date cannot be empty.\n";
                continue;
            }

            if (!regex_match(input, datePattern)) {
                cout << "[ERROR] Invalid date format. Use YYYY-MM-DD (e.g., 2025-06-26).\n";
                continue;
            }

            // Basic validation of month and day ranges
            int year = stoi(input.substr(0, 4));
            int month = stoi(input.substr(5, 2));
            int day = stoi(input.substr(8, 2));

            if (month < 1 || month > 12) {
                cout << "[ERROR] Month must be between 01 and 12.\n";
                continue;
            }

            if (day < 1 || day > 31) {
                cout << "[ERROR] Day must be between 01 and 31.\n";
                continue;
            }

            // Simple check for days in month
            if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
                cout << "[ERROR] This month has only 30 days.\n";
                continue;
            }

            if (month == 2 && day > 29) {
                cout << "[ERROR] February has at most 29 days.\n";
                continue;
            }

            if (year < 1900 || year > 2100) {
                cout << "[ERROR] Year must be between 1900 and 2100.\n";
                continue;
            }

            return input;
        }
    }

    // Get validated time in HH:MM format (24-hour)
    static string getValidatedTime(const string& prompt) {
        string input;
        regex timePattern(R"(\d{2}:\d{2})");
        
        while (true) {
            cout << "\n>> " << prompt;
            getline(cin, input);
            input = trim(input);

            if (input.empty()) {
                cout << "[ERROR] Time cannot be empty.\n";
                continue;
            }

            if (!regex_match(input, timePattern)) {
                cout << "[ERROR] Invalid time format. Use HH:MM (e.g., 09:30 or 14:45).\n";
                continue;
            }

            int hour = stoi(input.substr(0, 2));
            int minute = stoi(input.substr(3, 2));

            if (hour < 0 || hour > 23) {
                cout << "[ERROR] Hour must be between 00 and 23.\n";
                continue;
            }

            if (minute < 0 || minute > 59) {
                cout << "[ERROR] Minute must be between 00 and 59.\n";
                continue;
            }

            return input;
        }
    }

    // Get validated password (with basic requirements)
    static string getValidatedPassword(const string& prompt, bool requireStrong = false) {
        string input;
        while (true) {
            cout << "\n>> " << prompt;
            getline(cin, input);
            input = trim(input);

            if (input.empty()) {
                cout << "[ERROR] Password cannot be empty.\n";
                continue;
            }

            if (input.length() < 6) {
                cout << "[ERROR] Password must be at least 6 characters long.\n";
                continue;
            }

            if (requireStrong) {
                bool hasUpper = false, hasLower = false, hasDigit = false;
                for (char c : input) {
                    if (isupper(c)) hasUpper = true;
                    if (islower(c)) hasLower = true;
                    if (isdigit(c)) hasDigit = true;
                }

                if (!hasUpper || !hasLower || !hasDigit) {
                    cout << "[ERROR] Password must contain at least one uppercase, one lowercase, and one digit.\n";
                    continue;
                }
            }

            return input;
        }
    }

    // Get yes/no confirmation
    static bool getConfirmation(const string& prompt) {
        string input;
        while (true) {
            cout << "\n>> " << prompt << " (yes/no): ";
            getline(cin, input);
            input = trim(input);

            // Convert to lowercase for comparison
            for (char& c : input) {
                c = tolower(c);
            }

            if (input == "yes" || input == "y") return true;
            if (input == "no" || input == "n") return false;

            cout << "[ERROR] Please enter 'yes' or 'no'.\n";
        }
    }
};

#endif // MODULE_H