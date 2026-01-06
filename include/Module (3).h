#ifndef MODULE_3_H
#define MODULE_3_H

#include <iostream>
#include <string>
#include "Module.h"
#include "Module (2).h"
#include "Module (4).h"

using namespace std;

class DoctorUnit : public BaseInterface {
    string area;

public:
    DoctorUnit(string id, string n, string e, string p, string s)
        : BaseInterface(id, n, e, p, "Doctor"), area(s) {}

    void showDashboard() override {
        int pick = 0;
        do {
            cout << "\n================== DOCTOR DASHBOARD ==================\n";
            cout << "[1]. View My Schedule\n";
            cout << "[2]. Add Medical Record\n";
            cout << "[3]. View Patient Records\n";
            cout << "[4]. View Bills\n";
            cout << "[5]. Logout\n";
            cout << "======================================================\n";
            pick = InputTools::getValidatedInteger("Select option: ", 1, 5);

            if (pick == 1)
                DataControl::getInstance()->displayAppointments();
            else if (pick == 2)
                DataControl::getInstance()->inputMedicalRecord(fullName);
            else if (pick == 3)
                DataControl::getInstance()->printRecordsForPatient(InputTools::getValidatedString("Enter Patient ID: "));
            else if (pick == 4)
                DataControl::getInstance()->showBills(InputTools::getValidatedString("Enter Patient ID: "));

        } while (pick != 5);
    }
};

class PatientUnit : public BaseInterface {
    string mobile, location;

public:
    PatientUnit(string id, string n, string e, string p, string ph, string addr)
        : BaseInterface(id, n, e, p, "Patient"), mobile(ph), location(addr) {}

    void showDashboard() override {
        int choice = 0;
        do {
            cout << "\n================== PATIENT DASHBOARD =================\n";
            cout << "[1]. Book Appointment\n";
            cout << "[2]. View Appointments\n";
            cout << "[3]. Cancel Appointment\n";
            cout << "[4]. View Medical Records\n";
            cout << "[5]. View Bills\n";
            cout << "[6]. Update Profile\n";
            cout << "[7]. Logout\n";
            cout << "======================================================\n";
            choice = InputTools::getValidatedInteger("Select option: ", 1, 7);

            if (choice == 1)
                DataControl::getInstance()->makeAppointment(uid);
            else if (choice == 2)
                DataControl::getInstance()->displayAppointments();
            else if (choice == 3)
                DataControl::getInstance()->removeAppointment(InputTools::getValidatedString("Enter Appointment ID to cancel: "));
            else if (choice == 4)
                DataControl::getInstance()->printRecordsForPatient(uid);
            else if (choice == 5)
                DataControl::getInstance()->showBills(uid);
            else if (choice == 6) {
                mobile = InputTools::getValidatedString("Enter new phone: ");
                location = InputTools::getValidatedString("Enter new address: ");
                DataControl::getInstance()->reviseUserProfile(uid, mobile, location);
            }

        } while (choice != 7);
    }
};

class FrontDesk : public BaseInterface {
public:
    FrontDesk(string id, string n, string e, string p)
        : BaseInterface(id, n, e, p, "Receptionist") {}

    void showDashboard() override {
        int action = 0;
        do {
            cout << "\n================ RECEPTIONIST DASHBOARD ==============\n";
            cout << "[1]. Register New Patient\n";
            cout << "[2]. Schedule Appointment\n";
            cout << "[3]. Assign Room\n";
            cout << "[4]. Handle Payment\n";
            cout << "[5]. View All Patients\n";
            cout << "[6]. View Bills\n";
            cout << "[7]. View Room Assignments\n";
            cout << "[8]. Logout\n";
            cout << "======================================================\n";
            action = InputTools::getValidatedInteger("Choose option: ", 1, 8);

            if (action == 1)
                DataControl::getInstance()->registerNewPatient();
            else if (action == 2)
                DataControl::getInstance()->makeAppointmentManual();
            else if (action == 3)
                DataControl::getInstance()->assignRoomToPatient();
            else if (action == 4)
                DataControl::getInstance()->handleBilling();
            else if (action == 5)
                DataControl::getInstance()->listAllPatients();
            else if (action == 6)
                DataControl::getInstance()->showBills(InputTools::getValidatedString("Enter Patient ID: "));
            else if (action == 7)
                DataControl::getInstance()->viewRoomAssignments();

        } while (action != 8);
    }
};

class AdminUnit : public BaseInterface {
public:
    AdminUnit(string id, string n, string e, string p)
        : BaseInterface(id, n, e, p, "Admin") {}

    void showDashboard() override {
        int input = 0;
        do {
            cout << "\n=================== ADMIN DASHBOARD ==================\n";
            cout << "[1]. Add Doctor\n";
            cout << "[2]. Add Receptionist\n";
            cout << "[3]. Remove Staff\n";
            cout << "[4]. View Appointments\n";
            cout << "[5]. View Patient Bills\n";
            cout << "[6]. View Room Assignments\n";
            cout << "[7]. Logout\n";
            cout << "======================================================\n";
            input = InputTools::getValidatedInteger("Select action: ", 1, 7);

            if (input == 1)
                DataControl::getInstance()->registerNewDoctor();
            else if (input == 2)
                DataControl::getInstance()->registerNewReceptionist();
            else if (input == 3)
                DataControl::getInstance()->removeUserById();
            else if (input == 4)
                DataControl::getInstance()->displayAppointments();
            else if (input == 5)
                DataControl::getInstance()->showBills(InputTools::getValidatedString("Enter patient ID: "));
            else if (input == 6)
                DataControl::getInstance()->viewRoomAssignments();

        } while (input != 7);
    }
};

#endif // MODULE_3_H
