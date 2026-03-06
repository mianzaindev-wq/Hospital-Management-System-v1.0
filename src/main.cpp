#include <iostream>
#include <string>

#include "../include/hms/InputTools.h"
#include "../include/hms/AccountGenerator.h"
#include "../include/hms/EngineLoader.h"
#include "../include/hms/Roles.h"         // for BaseInterface

int main() {
    using namespace hms;

    InputTools::clearScreen();
    EngineLoader::initializeEngine();

    std::cout << "\n=====================================================\n";
    std::cout << "           WELCOME TO HOSPITAL MANAGEMENT SYSTEM      \n";
    std::cout << "=====================================================\n";

    while (true) {
        InputTools::clearScreen();
        std::cout << "\n-------------------- MAIN MENU ----------------------\n";
        std::cout << "[1] Login\n";
        std::cout << "[2] Sign up\n";
        std::cout << "[3] Exit\n";
        std::cout << "-----------------------------------------------------\n";

        int userInput = InputTools::getValidatedInteger("Enter your choice (1-3): ", 1, 3);

        if (userInput == 1) {
            std::cout << "\n--------------------- LOGIN PANEL -------------------\n";
            std::string inputEmail = InputTools::getValidatedEmail("Enter email address     : ");
            std::string inputPassword = InputTools::getValidatedPassword("Enter password          : ", true);

            try {
                BaseInterface* activeUser = AccountGenerator::verifyAndLogin(inputEmail, inputPassword);
                if (activeUser) {
                    std::cout << "\n[INFO] Login successful! Welcome, " << activeUser->getFullName() << ".\n";
                    std::cout << "-----------------------------------------------------\n";
                    activeUser->showDashboard();
                } else {
                    std::cout << "\n[ERROR] Login failed. Invalid email or password.\n";
                }
            } catch (const std::exception& ex) {
                std::cout << "[ERROR] " << ex.what() << "\n";
            }

            InputTools::pause();
        } else if (userInput == 2) {
            // patient signup
            std::cout << "\n------------------ PATIENT SIGN UP ------------------\n";
            try {
                DataControl::getInstance()->registerNewPatient();
            } catch (const std::exception& ex) {
                std::cout << "[ERROR] " << ex.what() << "\n";
            }
            InputTools::pause();
        } else if (userInput == 3) {
            std::cout << "\n[INFO] Thank you for using the Hospital Management System!\n";
            std::cout << "=====================================================\n";
            break;
        }
    }

    return 0;
}
