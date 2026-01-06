#include <iostream>
#include <string>
#include "Module.h"
#include "Module (2).h"
#include "Module (3).h"
#include "Module (5).h"
#include "Module (6).h"

using namespace std;

int main() {
    EngineLoader::initializeEngine();

    cout << "\n=====================================================\n";
    cout << "           WELCOME TO HOSPITAL MANAGEMENT SYSTEM      \n";
    cout << "=====================================================\n";

    while (true) {
        cout << "\n-------------------- MAIN MENU ----------------------\n";
        cout << "[1]. Login\n";
        cout << "[2]. Exit\n";
        cout << "-----------------------------------------------------\n";

        int userInput = InputTools::getValidatedInteger("Enter your choice (1-2): ", 1, 2);

        if (userInput == 1) {
            cout << "\n--------------------- LOGIN PANEL -------------------\n";
            string inputEmail = InputTools::getValidatedString("Enter email address     : ");
            string inputPassword = InputTools::getValidatedString("Enter password          : ");

            BaseInterface* activeUser = AccountGenerator::verifyAndLogin(inputEmail, inputPassword);

            if (activeUser) {
                cout << "\n[INFO] Login successful! Welcome, " << activeUser->getFullName() << ".\n";
                cout << "-----------------------------------------------------\n";
                activeUser->showDashboard();
                activeUser = nullptr; // Optional: allows next login cleanly
            } else {
                cout << "\n[ERROR] Login failed. Invalid email or password.\n";
            }
        } else if (userInput == 2) {
            cout << "\n[INFO] Thank you for using the Hospital Management System!\n";
            cout << "=====================================================\n";
            break;
        }
    }

    return 0;
}
