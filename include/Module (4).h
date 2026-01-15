#ifndef MODULE_4_H
#define MODULE_4_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include "Module.h"
#include "Module (2).h"
#include "Module (5).h"

using namespace std;

class AppointmentItem {
public:
    string aid;
    string pid;
    string did;
    string date;
    string time;
    string status;

    AppointmentItem() : status("Scheduled") {}
    
    AppointmentItem(const string& appointmentId, const string& patientId, 
                    const string& doctorId, const string& appointmentDate, 
                    const string& appointmentTime)
        : aid(appointmentId), pid(patientId), did(doctorId), 
          date(appointmentDate), time(appointmentTime), status("Scheduled") {}
};

class MedicalNote {
public:
    string rid;
    string pid;
    string did;
    string date;
    string diagnosis;
    string remedy;

    MedicalNote() {}
    
    MedicalNote(const string& recordId, const string& patientId, 
                const string& doctorId, const string& recordDate, 
                const string& diag, const string& treatment)
        : rid(recordId), pid(patientId), did(doctorId), 
          date(recordDate), diagnosis(diag), remedy(treatment) {}
};

class BillingItem {
public:
    string bid;
    string pid;
    string date;
    string label;
    double cost;

    BillingItem() : cost(0.0), label("Unpaid") {}
    
    BillingItem(const string& billId, const string& patientId, 
                const string& billDate, double amount)
        : bid(billId), pid(patientId), date(billDate), 
          cost(amount), label("Unpaid") {}
};

class RoomSpot {
public:
    string roomNum;
    string assignedPid;
    bool filled;

    RoomSpot() : filled(false) {}
    
    explicit RoomSpot(const string& roomNumber) 
        : roomNum(roomNumber), filled(false) {}
};

// CRITICAL: Singleton pattern for managing all hospital data
// Uses vectors instead of raw arrays for automatic memory management
class DataControl {
private:
    // MAJOR CHANGE: vectors instead of raw arrays
    // vectors automatically manage memory (no manual delete needed)
    // vectors grow dynamically (no fixed size limits)
    vector<unique_ptr<BaseInterface>> userList;  // unique_ptr ensures automatic cleanup
    vector<AppointmentItem> appointmentList;
    vector<MedicalNote> recordList;
    vector<BillingItem> billList;
    vector<RoomSpot> roomList;

    static DataControl* handler;

    DataControl() {
        roomList.reserve(20);  // Pre-allocate space for efficiency
        for (int i = 1; i <= 20; ++i) {
            roomList.push_back(RoomSpot("R" + to_string(i)));
        }
    }

    // Prevent copying (singleton pattern)
    DataControl(const DataControl&) = delete;
    DataControl& operator=(const DataControl&) = delete;

public:
    static DataControl* getInstance() {
        if (!handler) {
            handler = new DataControl();
        }
        return handler;
    }

    // CRITICAL: Cleanup singleton on program exit
    static void destroyInstance() {
        delete handler;
        handler = nullptr;
    }

    ~DataControl() {
        // unique_ptr automatically cleans up all users
        // vectors automatically clean up their contents
    }

    BaseInterface* validateUser(const string& mail, const string& pass) {
        for (const auto& user : userList) {
            if (user->authenticate(mail, pass)) {
                return user.get();  // Return raw pointer (ownership stays with unique_ptr)
            }
        }
        return nullptr;
    }

    // MAJOR CHANGE: Takes ownership via unique_ptr
    void pushUser(unique_ptr<BaseInterface> u) {
        // Check for duplicate ID
        for (const auto& user : userList) {
            if (user->getUserId() == u->getUserId()) {
                cout << "[ERROR] Duplicate ID found: " << u->getUserId() << "\n";
                return;
            }
            if (user->getEmailId() == u->getEmailId()) {
                cout << "[ERROR] Duplicate email found: " << u->getEmailId() << "\n";
                return;
            }
        }
        
        cout << "[SUCCESS] User " << u->getUserId() << " added successfully.\n";
        userList.push_back(std::move(u));  // Transfer ownership to vector
    }

    void registerNewDoctor();
    void registerNewPatient();
    void registerNewReceptionist();
    void removeUserById();

    void displayAppointments();
    void makeAppointment(const string& patientId);
    void makeAppointmentManual();
    void removeAppointment(const string& aid);
    
    void inputMedicalRecord(const string& docName);
    void printRecordsForPatient(const string& pid);
    
    void showBills(const string& pid);
    void handleBilling();
    
    void assignRoomToPatient();
    void viewRoomAssignments();
    
    void listAllPatients();
    void listAllUsers();
    void reviseUserProfile(const string& uid, const string& phone, const string& addr);

    // Utility functions
    size_t getUserCount() const { return userList.size(); }
    size_t getAppointmentCount() const { return appointmentList.size(); }
    size_t getRecordCount() const { return recordList.size(); }
    size_t getBillCount() const { return billList.size(); }
};

DataControl* DataControl::handler = nullptr;

void DataControl::registerNewDoctor() {
    string id = InputTools::getValidatedString("Doctor ID: ");
    string name = InputTools::getValidatedString("Name: ");
    string email = InputTools::getValidatedEmail("Email: ");
    string pass = InputTools::getValidatedPassword("Password: ");
    string specialty = InputTools::getValidatedString("Specialization: ");
    
    auto newDoc = make_unique<DoctorUnit>(id, name, email, pass, specialty);
    pushUser(std::move(newDoc));
}

void DataControl::registerNewPatient() {
    string id = InputTools::getValidatedString("Patient ID: ");
    string name = InputTools::getValidatedString("Name: ");
    string email = InputTools::getValidatedEmail("Email: ");
    string pass = InputTools::getValidatedPassword("Password: ");
    string phone = InputTools::getValidatedPhone("Phone: ");
    string address = InputTools::getValidatedString("Address: ");
    
    auto newPat = make_unique<PatientUnit>(id, name, email, pass, phone, address);
    pushUser(std::move(newPat));
}

void DataControl::registerNewReceptionist() {
    string id = InputTools::getValidatedString("Receptionist ID: ");
    string name = InputTools::getValidatedString("Name: ");
    string email = InputTools::getValidatedEmail("Email: ");
    string pass = InputTools::getValidatedPassword("Password: ");
    
    auto newRec = make_unique<FrontDesk>(id, name, email, pass);
    pushUser(std::move(newRec));
}

void DataControl::removeUserById() {
    string id = InputTools::getValidatedString("Enter ID to remove: ");
    
    if (!InputTools::getConfirmation("Are you sure you want to delete user " + id + "?")) {
        cout << "[INFO] Deletion cancelled.\n";
        return;
    }

    // Find and remove user
    auto userIt = find_if(userList.begin(), userList.end(),
        [&id](const unique_ptr<BaseInterface>& user) {
            return user->getUserId() == id;
        });

    if (userIt == userList.end()) {
        cout << "[ERROR] User ID not found.\n";
        return;
    }

    userList.erase(userIt);  // unique_ptr automatically deletes the object

    // Remove associated appointments
    appointmentList.erase(
        remove_if(appointmentList.begin(), appointmentList.end(),
            [&id](const AppointmentItem& apt) {
                return apt.pid == id || apt.did == id;
            }),
        appointmentList.end()
    );

    cout << "[SUCCESS] User " << id << " removed.\n";
}

void DataControl::displayAppointments() {
    if (appointmentList.empty()) {
        cout << "[INFO] No appointments scheduled.\n";
        return;
    }
    
    cout << "\n================ APPOINTMENTS ================\n";
    for (const auto& apt : appointmentList) {
        cout << "ID: " << apt.aid 
             << " | Patient: " << apt.pid
             << " | Doctor: " << apt.did
             << " | Date: " << apt.date
             << " | Time: " << apt.time
             << " | Status: " << apt.status << "\n";
    }
    cout << "==============================================\n";
}

void DataControl::makeAppointment(const string& patientId) {
    string docId = InputTools::getValidatedString("Enter Doctor ID: ");
    string date = InputTools::getValidatedDate("Date (YYYY-MM-DD): ");
    string time = InputTools::getValidatedTime("Time (HH:MM): ");

    // Check for conflicts
    for (const auto& apt : appointmentList) {
        if (apt.date == date && apt.time == time &&
            (apt.pid == patientId || apt.did == docId)) {
            cout << "[ERROR] Overlapping appointment detected!\n";
            return;
        }
    }

    string aid = "A" + to_string(appointmentList.size() + 1);
    appointmentList.emplace_back(aid, patientId, docId, date, time);
    cout << "[SUCCESS] Appointment booked successfully. ID: " << aid << "\n";
}

void DataControl::makeAppointmentManual() {
    string pid = InputTools::getValidatedString("Enter Patient ID: ");
    makeAppointment(pid);
}

void DataControl::removeAppointment(const string& aid) {
    auto it = find_if(appointmentList.begin(), appointmentList.end(),
        [&aid](const AppointmentItem& apt) {
            return apt.aid == aid;
        });

    if (it != appointmentList.end()) {
        appointmentList.erase(it);
        cout << "[SUCCESS] Appointment cancelled.\n";
    } else {
        cout << "[ERROR] Appointment ID not found.\n";
    }
}

void DataControl::inputMedicalRecord(const string& docName) {
    string pid = InputTools::getValidatedString("Patient ID: ");
    string date = InputTools::getValidatedDate("Date (YYYY-MM-DD): ");
    string diagnosis = InputTools::getValidatedString("Diagnosis: ");
    string treatment = InputTools::getValidatedString("Treatment: ");
    
    string rid = "R" + to_string(recordList.size() + 1);
    recordList.emplace_back(rid, pid, docName, date, diagnosis, treatment);
    cout << "[SUCCESS] Medical record added. ID: " << rid << "\n";
}

void DataControl::printRecordsForPatient(const string& pid) {
    bool found = false;
    cout << "\n================ MEDICAL RECORDS ================\n";
    for (const auto& rec : recordList) {
        if (rec.pid == pid) {
            found = true;
            cout << "Record ID: " << rec.rid << "\n";
            cout << "Date: " << rec.date << "\n";
            cout << "Doctor: " << rec.did << "\n";
            cout << "Diagnosis: " << rec.diagnosis << "\n";
            cout << "Treatment: " << rec.remedy << "\n";
            cout << "-------------------------------------------------\n";
        }
    }
    if (!found) {
        cout << "No records found for Patient ID: " << pid << "\n";
    }
    cout << "=================================================\n";
}

void DataControl::showBills(const string& pid) {
    bool found = false;
    cout << "\n================ BILLING INFORMATION ================\n";
    for (const auto& bill : billList) {
        if (bill.pid == pid) {
            found = true;
            cout << "Bill ID: " << bill.bid 
                 << " | Amount: $" << bill.cost
                 << " | Date: " << bill.date
                 << " | Status: " << bill.label << "\n";
        }
    }
    if (!found) {
        cout << "No bills found for Patient ID: " << pid << "\n";
    }
    cout << "=====================================================\n";
}

void DataControl::handleBilling() {
    string pid = InputTools::getValidatedString("Patient ID: ");
    string bid = "B" + to_string(billList.size() + 1);
    double amt = InputTools::getValidatedDouble("Amount: $", 0.0);

    string date = InputTools::getValidatedDate("Date (YYYY-MM-DD): ");
    billList.emplace_back(bid, pid, date, amt);
    cout << "[SUCCESS] Bill created. ID: " << bid << "\n";
}

void DataControl::assignRoomToPatient() {
    string pid = InputTools::getValidatedString("Patient ID: ");
    string roomNum = InputTools::getValidatedString("Room Number: ");

    // Check if patient already has a room
    for (const auto& room : roomList) {
        if (room.assignedPid == pid) {
            cout << "[ERROR] Patient already has room " << room.roomNum << " assigned.\n";
            return;
        }
    }

    // Find and assign room
    for (auto& room : roomList) {
        if (room.roomNum == roomNum) {
            if (room.filled) {
                cout << "[ERROR] Room already occupied by patient " << room.assignedPid << ".\n";
                return;
            }
            room.assignedPid = pid;
            room.filled = true;
            cout << "[SUCCESS] Room " << roomNum << " assigned to patient " << pid << ".\n";
            return;
        }
    }
    cout << "[ERROR] Room number not found.\n";
}

void DataControl::viewRoomAssignments() {
    bool anyAssigned = false;
    cout << "\n================ ROOM ASSIGNMENTS ================\n";
    for (const auto& room : roomList) {
        if (room.filled) {
            cout << "Room " << room.roomNum 
                 << " → Patient ID: " << room.assignedPid << "\n";
            anyAssigned = true;
        }
    }
    if (!anyAssigned) {
        cout << "No rooms are currently assigned.\n";
    }
    cout << "==================================================\n";
}

void DataControl::listAllPatients() {
    bool found = false;
    cout << "\n================ ALL PATIENTS ================\n";
    for (const auto& user : userList) {
        if (user->isPatient()) {
            found = true;
            cout << "ID: " << user->getUserId() 
                 << " | Name: " << user->getFullName() 
                 << " | Email: " << user->getEmailId() << "\n";
        }
    }
    if (!found) {
        cout << "No patients registered.\n";
    }
    cout << "==============================================\n";
}

void DataControl::listAllUsers() {
    cout << "\n================ ALL USERS ================\n";
    for (const auto& user : userList) {
        cout << "ID: " << user->getUserId() 
             << " | Name: " << user->getFullName() 
             << " | Role: " << user->getRoleType() 
             << " | Email: " << user->getEmailId() << "\n";
    }
    cout << "Total Users: " << userList.size() << "\n";
    cout << "===========================================\n";
}

void DataControl::reviseUserProfile(const string& uid, const string& phone, const string& addr) {
    auto it = find_if(userList.begin(), userList.end(),
        [&uid](const unique_ptr<BaseInterface>& user) {
            return user->getUserId() == uid;
        });

    if (it != userList.end()) {
        // Downcast to PatientUnit to access patient-specific methods
        if ((*it)->isPatient()) {
            PatientUnit* patient = dynamic_cast<PatientUnit*>(it->get());
            if (patient) {
                patient->setPhoneNumber(phone);
                patient->setAddress(addr);
                cout << "[SUCCESS] Profile updated for patient " << uid << ".\n";
                return;
            }
        }
        cout << "[ERROR] Profile update only available for patients.\n";
    } else {
        cout << "[ERROR] User ID not found.\n";
    }
    
}

#endif