#ifndef HMS_INPUTTOOLS_H
#define HMS_INPUTTOOLS_H

#include <iostream>
#include <string>
#include <limits>

namespace hms {

class InputTools {
public:
    // remove leading/trailing whitespace
    static std::string trim(const std::string& str);

    // clear any leftover characters from std::cin
    static void clearInputBuffer();

    // basic validators
    static int getValidatedInteger(const std::string& prompt,
                                   int min = std::numeric_limits<int>::min(),
                                   int max = std::numeric_limits<int>::max());

    static std::string getValidatedString(const std::string& prompt);
    static double getValidatedDouble(const std::string& prompt, double min = 0.0);
    static std::string getValidatedEmail(const std::string& prompt);
    static std::string getValidatedPhone(const std::string& prompt);
    static std::string getValidatedDate(const std::string& prompt);
    static std::string getValidatedTime(const std::string& prompt);
    static std::string getValidatedPassword(const std::string& prompt, bool requireStrong = false);
    static bool getConfirmation(const std::string& prompt);

    // UI helpers
    static void clearScreen();
    static void pause(const std::string& message = "Press ENTER to continue...");
};

} // namespace hms

#endif // HMS_INPUTTOOLS_H
