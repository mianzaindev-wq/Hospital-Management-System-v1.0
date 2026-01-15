#ifndef MODULE_3_H
#define MODULE_3_H

#include <iostream>
#include <string>
#include "Module.h"
#include "Module (2).h"
#include "Module (4).h"

using namespace std;

class DoctorUnit : public BaseInterface {
private:
    string specialization;

public:
    DoctorUnit(const string& id, const string& name, const string& email, 
               const string& pass, const string& spec)
        : BaseInterface(id, name, email, pass, "Doctor"), specialization(spec) {}

    // Virtual destructor inherited from BaseInterface
    virtual ~DoctorUnit() {}

    const string& getSpecialization() const { return specialization; }
    void setSpecialization(const string& spec) { specialization = spec; }

    void showDashboard() override {
        int choice = 0;
        do {
            cout << "\n================== DOCTOR DASHBOARD ==================\n";
            cout << "[1]. View My Schedule\n";
            cout << "[2]. Add Medical Record\n";
            cout << "[3]. View Patient Records\n";
            cout << "[4]. View Bills\n";
            cout << "[5]. Logout\n";
            cout << "======================================================\n";
            choice = InputTools::getValidatedInteger("Select option: ", 1, 5);

            switch (choice) {
                case 1:
                    DataControl::getInstance()->displayAppointments();
                    break;
                case 2:
                    DataControl::getInstance()->inputMedicalRecord(fullName);
                    break;
                case 3: {
                    string pid = InputTools::getValidatedString("Enter Patient ID: ");
                    DataControl::getInstance()->printRecordsForPatient(pid);
                    break;
                }
                case 4: {
                    string pid = InputTools::getValidatedString("Enter Patient ID: ");
                    DataControl::getInstance()->showBills(pid);
                    break;
                }
                case 5:
                    cout << "[INFO] Logging out...\n";
                    break;
            }
        } while (choice != 5);
    }

    void displayInfo() const override {
        BaseInterface::displayInfo();
        cout << "Specialization: " << specialization << "\n";
        cout << "==================================================\n";
    }
};

class PatientUnit : public BaseInterface {
private:
    string phoneNumber;
    string address;

public:
    PatientUnit(const string& id, const string& name, const string& email, 
                const string& pass, const string& phone, const string& addr)
        : BaseInterface(id, name, email, pass, "Patient"), 
          phoneNumber(phone), address(addr) {}

    virtual ~PatientUnit() {}

    const string& getPhoneNumber() const { return phoneNumber; }
    const string& getAddress() const { return address; }
    
    void setPhoneNumber(const string& phone) { phoneNumber = phone; }
    void setAddress(const string& addr) { address = addr; }

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

            switch (choice) {
                case 1:
                    DataControl::getInstance()->makeAppointment(uid);
                    break;
                case 2:
                    DataControl::getInstance()->displayAppointments();
                    break;
                case 3: {
                    string aid = InputTools::getValidatedString("Enter Appointment ID to cancel: ");
                    DataControl::getInstance()->removeAppointment(aid);
                    break;
                }
                case 4:
                    DataControl::getInstance()->printRecordsForPatient(uid);
                    break;
                case 5:
                    DataControl::getInstance()->showBills(uid);
                    break;
                case 6: {
                    string newPhone = InputTools::getValidatedPhone("Enter new phone: ");
                    string newAddr = InputTools::getValidatedString("Enter new address: ");
                    setPhoneNumber(newPhone);
                    setAddress(newAddr);
                    DataControl::getInstance()->reviseUserProfile(uid, newPhone, newAddr);
                    cout << "[SUCCESS] Profile updated.\n";
                    break;
                }
                case 7:
                    cout << "[INFO] Logging out...\n";
                    break;
            }
        } while (choice != 7);
    }

    void displayInfo() const override {
        BaseInterface::displayInfo();
        cout << "Phone    : " << phoneNumber << "\n";
        cout << "Address  : " << address << "\n";
        cout << "==================================================\n";
    }
};

class FrontDesk : public BaseInterface {
public:
    FrontDesk(const string& id, const string& name, const string& email, const string& pass)
        : BaseInterface(id, name, email, pass, "Receptionist") {}

    virtual ~FrontDesk() {}

    void showDashboard() override {
        int choice = 0;
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
            choice = InputTools::getValidatedInteger("Choose option: ", 1, 8);

            switch (choice) {
                case 1:
                    DataControl::getInstance()->registerNewPatient();
                    break;
                case 2:
                    DataControl::getInstance()->makeAppointmentManual();
                    break;
                case 3:
                    DataControl::getInstance()->assignRoomToPatient();
                    break;
                case 4:
                    DataControl::getInstance()->handleBilling();
                    break;
                case 5:
                    DataControl::getInstance()->listAllPatients();
                    break;
                case 6: {
                    string pid = InputTools::getValidatedString("Enter Patient ID: ");
                    DataControl::getInstance()->showBills(pid);
                    break;
                }
                case 7:
                    DataControl::getInstance()->viewRoomAssignments();
                    break;
                case 8:
                    cout << "[INFO] Logging out...\n";
                    break;
            }
        } while (choice != 8);
    }
};

class AdminUnit : public BaseInterface {
public:
    AdminUnit(const string& id, const string& name, const string& email, const string& pass)
        : BaseInterface(id, name, email, pass, "Admin") {}

    virtual ~AdminUnit() {}

    void showDashboard() override {
        int choice = 0;
        do {
            cout << "\n=================== ADMIN DASHBOARD ==================\n";
            cout << "[1]. Add Doctor\n";
            cout << "[2]. Add Receptionist\n";
            cout << "[3]. Remove Staff\n";
            cout << "[4]. View Appointments\n";
            cout << "[5]. View Patient Bills\n";
            cout << "[6]. View Room Assignments\n";
            cout << "[7]. View All Users\n";
            cout << "[8]. Logout\n";
            cout << "======================================================\n";
            choice = InputTools::getValidatedInteger("Select action: ", 1, 8);

            switch (choice) {
                case 1:
                    DataControl::getInstance()->registerNewDoctor();
                    break;
                case 2:
                    DataControl::getInstance()->registerNewReceptionist();
                    break;
                case 3:
                    DataControl::getInstance()->removeUserById();
                    break;
                case 4:
                    DataControl::getInstance()->displayAppointments();
                    break;
                case 5: {
                    string pid = InputTools::getValidatedString("Enter patient ID: ");
                    DataControl::getInstance()->showBills(pid);
                    break;
                }
                case 6:
                    DataControl::getInstance()->viewRoomAssignments();
                    break;
                case 7:
                    DataControl::getInstance()->listAllUsers();
                    break;
                case 8:
                    cout << "[INFO] Logging out...\n";
                    break;
            }
        } while (choice != 8);
    }
};

#endif