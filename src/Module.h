#ifndef MODULE_H
#define MODULE_H

#include <iostream>
#include <string>
using namespace std;

class InputTools {
private:
    static string trim(const string& str) {
        size_t start = 0;
        while (start < str.length() && (str[start] == ' ' || str[start] == '\t' || str[start] == '\n' || str[start] == '\r')) {
            start++;
        }

        size_t end = str.length();
        while (end > start && (str[end - 1] == ' ' || str[end - 1] == '\t' || str[end - 1] == '\n' || str[end - 1] == '\r')) {
            end--;
        }

        return str.substr(start, end - start);
    }

public:
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
                int result = stoi(input);
                if (result < min || result > max) {
                    cout << "[ERROR] Number out of range. Please try again.\n";
                    continue;
                }
                return result;
            } catch (...) {
                cout << "[ERROR] Conversion error. Try again.\n";
            }
        }
    }

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
                cout << "[ERROR] Invalid number format. Only digits and one decimal allowed.\n";
                continue;
            }

            try {
                double result = stod(input);
                if (result < min) {
                    cout << "[ERROR] Value is below the allowed minimum.\n";
                    continue;
                }
                return result;
            } catch (...) {
                cout << "[ERROR] Conversion error. Try again.\n";
            }
        }
    }
};

#endif
