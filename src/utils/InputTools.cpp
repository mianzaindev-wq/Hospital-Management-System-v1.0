#include "../include/hms/InputTools.h"
#include <regex>
#include <limits>

namespace hms {

std::string InputTools::trim(const std::string& str) {
    if (str.empty()) return str;
    size_t start = 0;
    while (start < str.length() && isspace(static_cast<unsigned char>(str[start]))) {
        start++;
    }
    size_t end = str.length();
    while (end > start && isspace(static_cast<unsigned char>(str[end - 1]))) {
        end--;
    }
    return str.substr(start, end - start);
}

void InputTools::clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void InputTools::clearScreen() {
    // cross-platform simple clear using ANSI escape codes
    // if the terminal doesn't support it the output will still be readable
    std::cout << "\033[2J\033[H";
}

int InputTools::getValidatedInteger(const std::string& prompt, int min, int max) {
    std::string input;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, input);
        input = trim(input);

        if (input.empty()) {
            std::cout << "[ERROR] Input cannot be empty.\n";
            continue;
        }

        bool valid = true;
        size_t i = (input[0] == '-') ? 1 : 0;
        if (i >= input.length()) {
            std::cout << "[ERROR] Invalid number format.\n";
            continue;
        }
        for (; i < input.length(); ++i) {
            if (!isdigit(input[i])) { valid = false; break; }
        }
        if (!valid) {
            std::cout << "[ERROR] Invalid number. Please enter digits only.\n";
            continue;
        }

        try {
            long long temp = stoll(input);
            if (temp < min || temp > max) {
                std::cout << "[ERROR] Number out of range (" << min << " - " << max << ").\n";
                continue;
            }
            return static_cast<int>(temp);
        } catch (const std::out_of_range&) {
            std::cout << "[ERROR] Number too large.\n";
        } catch (...) {
            std::cout << "[ERROR] Conversion error.\n";
        }
    }
}

std::string InputTools::getValidatedString(const std::string& prompt) {
    std::string input;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, input);
        input = trim(input);
        if (!input.empty()) return input;
        std::cout << "[ERROR] Input cannot be empty.\n";
    }
}

// floating-point validator

double InputTools::getValidatedDouble(const std::string& prompt, double min) {
    std::string input;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, input);
        input = trim(input);
        if (input.empty()) {
            std::cout << "[ERROR] Input cannot be empty.\n";
            continue;
        }
        bool valid = true;
        bool dotSeen = false;
        size_t i = (input[0] == '-') ? 1 : 0;
        if (i >= input.length()) {
            std::cout << "[ERROR] Invalid number format.\n";
            continue;
        }
        for (; i < input.length(); ++i) {
            if (input[i] == '.') {
                if (dotSeen) { valid = false; break; }
                dotSeen = true;
            } else if (!isdigit(input[i])) {
                valid = false;
                break;
            }
        }
        if (!valid) {
            std::cout << "[ERROR] Invalid number format.\n";
            continue;
        }
        try {
            double result = stod(input);
            if (result < min) {
                std::cout << "[ERROR] Value must be at least " << min << ".\n";
                continue;
            }
            return result;
        } catch (const std::out_of_range&) {
            std::cout << "[ERROR] Number too large.\n";
        } catch (...) {
            std::cout << "[ERROR] Conversion error.\n";
        }
    }
}

// Additional validators use similar patterns to earlier implementation
// for brevity they are omitted here but would follow the same structure as before.

std::string InputTools::getValidatedEmail(const std::string& prompt) {
    std::regex pattern(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
    std::string input;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, input);
        input = trim(input);
        if (input.empty()) {
            std::cout << "[ERROR] Email cannot be empty.\n";
            continue;
        }
        if (std::regex_match(input, pattern)) return input;
        std::cout << "[ERROR] Invalid email format.\n";
    }
}

std::string InputTools::getValidatedPhone(const std::string& prompt) {
    std::string input;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, input);
        input = trim(input);
        if (input.empty()) {
            std::cout << "[ERROR] Phone number cannot be empty.\n";
            continue;
        }
        std::string cleaned;
        for (char c : input) {
            if (isdigit(c)) cleaned += c;
            else if (c != '-' && c != ' ' && c != '(' && c != ')' && c != '+') {
                cleaned.clear();
                break;
            }
        }
        if (!cleaned.empty() && cleaned.length() >= 10 && cleaned.length() <= 15) {
            return input;
        }
        std::cout << "[ERROR] Phone number must contain 10-15 digits.\n";
    }
}

std::string InputTools::getValidatedDate(const std::string& prompt) {
    std::regex pattern(R"(\d{4}-\d{2}-\d{2})");
    std::string input;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, input);
        input = trim(input);
        if (input.empty()) {
            std::cout << "[ERROR] Date cannot be empty.\n";
            continue;
        }
        if (!std::regex_match(input, pattern)) {
            std::cout << "[ERROR] Invalid date format. Use YYYY-MM-DD.\n";
            continue;
        }
        int year = stoi(input.substr(0, 4));
        int month = stoi(input.substr(5, 2));
        int day = stoi(input.substr(8, 2));
        bool bad = false;
        if (month < 1 || month > 12) bad = true;
        if (day < 1 || day > 31) bad = true;
        if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) bad = true;
        if (month == 2 && day > 29) bad = true;
        if (year < 1900 || year > 2100) bad = true;
        if (bad) {
            std::cout << "[ERROR] Invalid date value.\n";
            continue;
        }
        return input;
    }
}

std::string InputTools::getValidatedTime(const std::string& prompt) {
    std::regex pattern(R"(\d{2}:\d{2})");
    std::string input;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, input);
        input = trim(input);
        if (input.empty()) {
            std::cout << "[ERROR] Time cannot be empty.\n";
            continue;
        }
        if (!std::regex_match(input, pattern)) {
            std::cout << "[ERROR] Invalid time format.\n";
            continue;
        }
        int hour = stoi(input.substr(0, 2));
        int minute = stoi(input.substr(3, 2));
        if (hour < 0 || hour > 23 || minute < 0 || minute > 59) {
            std::cout << "[ERROR] Invalid hour/minute values.\n";
            continue;
        }
        return input;
    }
}

std::string InputTools::getValidatedPassword(const std::string& prompt, bool requireStrong) {
    std::string input;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, input);
        input = trim(input);
        if (input.empty()) {
            std::cout << "[ERROR] Password cannot be empty.\n";
            continue;
        }
        if (input.length() < 6) {
            std::cout << "[ERROR] Password too short (min 6).\n";
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
                std::cout << "[ERROR] Password must include upper, lower and digit.\n";
                continue;
            }
        }
        return input;
    }
}

bool InputTools::getConfirmation(const std::string& prompt) {
    std::string input;
    while (true) {
        std::cout << prompt << " (y/n): ";
        std::getline(std::cin, input);
        input = trim(input);
        for (auto &c : input) c = tolower(c);
        if (input == "y" || input == "yes") return true;
        if (input == "n" || input == "no") return false;
        std::cout << "[ERROR] Please answer yes or no.\n";
    }
}

void InputTools::pause(const std::string& message) {
    std::cout << message;
    std::string dummy;
    std::getline(std::cin, dummy);
}

} // namespace hms
