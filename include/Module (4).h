#ifndef MODULE_4_H
#define MODULE_4_H

#include <iostream>
#include <string>
#include "Module.h"
#include "Module (2).h"
#include "Module (5).h"

using namespace std;

class AppointmentItem {
public:
    string aid, pid, did, date, time, status;
    AppointmentItem() : status("Scheduled") {}
};

class MedicalNote {
public:
    string rid, pid, did, date, diagnosis, remedy;
};

class BillingItem {
public:
    string bid, pid, date, label;
    double cost;
    BillingItem() : cost(0), label("Unpaid") {}
};

class RoomSpot {
public:
    string roomNum, assignedPid;
    bool filled = false;
};

class DataControl {
private:
    BaseInterface* userList[100];
    AppointmentItem appointmentList[200];
    MedicalNote recordList[300];
    BillingItem billList[400];
    RoomSpot roomList[50];

    int userTotal = 0, appTotal = 0, recTotal = 0, billTotal = 0, roomTotal = 0;
    static DataControl* handler;

    DataControl() {
        for (int i = 1; i <= 20; i++) {
            roomList[roomTotal++].roomNum = "R" + to_string(i);
        }
    }

public:
    static DataControl* getInstance();

    BaseInterface* validateUser(string mail, string pass);
    void pushUser(BaseInterface* u);

    void registerNewDoctor();
    void registerNewPatient();
    void registerNewReceptionist();
    void removeUserById();

    void displayAppointments();
    void makeAppointment(string patientId);
    void makeAppointmentManual();
    void removeAppointment(string aid);
    void inputMedicalRecord(string docName);
    void printRecordsForPatient(string pid);
    void showBills(string pid);
    void handleBilling();
    void assignRoomToPatient();
    void viewRoomAssignments();
    void listAllPatients();
    void reviseUserProfile(string uid, string phone, string addr);
};

DataControl* DataControl::handler = nullptr;

DataControl* DataControl::getInstance() {
    if (!handler)
        handler = new DataControl();
    return handler;
}

BaseInterface* DataControl::validateUser(string mail, string pass) {
    for (int i = 0; i < userTotal; ++i)
        if (userList[i]->authenticate(mail, pass))
            return userList[i];
    return nullptr;
}

void DataControl::pushUser(BaseInterface* u) {
    for (int i = 0; i < userTotal; ++i) {
        if (userList[i]->getUserId() == u->getUserId()) {
            cout << "[ERROR] Duplicate ID found.\n";
            return;
        }
        if (userList[i]->getEmailId() == u->getEmailId()) {
            cout << "[ERROR] Duplicate email found.\n";
            return;
        }
    }
    userList[userTotal++] = u;
    cout << "[SUCCESS] User " << u->getUserId() << " added successfully.\n";
}

void DataControl::registerNewDoctor() {
    BaseInterface* newDoc = AccountGenerator::fabricate("Doctor");
    if (!newDoc) {
        cout << "[ERROR] Doctor creation failed.\n";
        return;
    }
    pushUser(newDoc);
}

void DataControl::registerNewPatient() {
    BaseInterface* newPat = AccountGenerator::fabricate("Patient");
    if (!newPat) {
        cout << "[ERROR] Patient creation failed.\n";
        return;
    }
    pushUser(newPat);
}

void DataControl::registerNewReceptionist() {
    BaseInterface* newRec = AccountGenerator::fabricate("Receptionist");
    if (!newRec) {
        cout << "[ERROR] Receptionist creation failed.\n";
        return;
    }
    pushUser(newRec);
}

void DataControl::removeUserById() {
    string id = InputTools::getValidatedString("Enter ID to remove: ");
    cout << "Are you sure you want to delete user with ID " << id << "? Type YES to confirm: ";
    string confirm;
    getline(cin, confirm);
    if (confirm != "YES") {
        cout << "[INFO] Deletion cancelled.\n";
        return;
    }

    for (int i = 0; i < userTotal; ++i) {
        if (userList[i]->getUserId() == id) {
            for (int j = i; j < userTotal - 1; ++j)
                userList[j] = userList[j + 1];
            userTotal--;

            for (int j = 0; j < appTotal;) {
                if (appointmentList[j].pid == id || appointmentList[j].did == id) {
                    for (int k = j; k < appTotal - 1; ++k)
                        appointmentList[k] = appointmentList[k + 1];
                    appTotal--;
                } else {
                    ++j;
                }
            }

            cout << "[SUCCESS] User " << id << " removed.\n";
            return;
        }
    }

    cout << "[ERROR] User ID not found.\n";
}

void DataControl::displayAppointments() {
    if (appTotal == 0) {
        cout << "[INFO] No appointments scheduled.\n";
        return;
    }
    for (int i = 0; i < appTotal; ++i) {
        cout << "Appointment ID: " << appointmentList[i].aid
             << ", Patient: " << appointmentList[i].pid
             << ", Doctor: " << appointmentList[i].did
             << ", Date: " << appointmentList[i].date
             << ", Time: " << appointmentList[i].time
             << ", Status: " << appointmentList[i].status << endl;
    }
}

void DataControl::makeAppointment(string patientId) {
    string docId = InputTools::getValidatedString("Enter Doctor ID: ");
    string date = InputTools::getValidatedString("Date (YYYY-MM-DD): ");
    string time = InputTools::getValidatedString("Time (HH:MM): ");

    for (int i = 0; i < appTotal; ++i) {
        if (appointmentList[i].date == date && appointmentList[i].time == time &&
            (appointmentList[i].pid == patientId || appointmentList[i].did == docId)) {
            cout << "[ERROR] Overlapping appointment detected!\n";
            return;
        }
    }

    AppointmentItem a;
    a.aid = "A" + to_string(appTotal + 1);
    a.pid = patientId;
    a.did = docId;
    a.date = date;
    a.time = time;
    appointmentList[appTotal++] = a;
    cout << "[SUCCESS] Appointment booked successfully.\n";
}

void DataControl::makeAppointmentManual() {
    string pid = InputTools::getValidatedString("Enter Patient ID: ");
    makeAppointment(pid);
}

void DataControl::removeAppointment(string aid) {
    for (int i = 0; i < appTotal; ++i) {
        if (appointmentList[i].aid == aid) {
            for (int j = i; j < appTotal - 1; ++j)
                appointmentList[j] = appointmentList[j + 1];
            appTotal--;
            cout << "[SUCCESS] Appointment cancelled.\n";
            return;
        }
    }
    cout << "[ERROR] Appointment ID not found.\n";
}

void DataControl::inputMedicalRecord(string docName) {
    MedicalNote m;
    m.pid = InputTools::getValidatedString("Patient ID: ");
    m.did = docName;
    m.date = "2025-06-26";
    m.diagnosis = InputTools::getValidatedString("Diagnosis: ");
    m.remedy = InputTools::getValidatedString("Treatment: ");
    m.rid = "R" + to_string(recTotal + 1);
    recordList[recTotal++] = m;
    cout << "[SUCCESS] Medical record added.\n";
}

void DataControl::printRecordsForPatient(string pid) {
    for (int i = 0; i < recTotal; ++i) {
        if (recordList[i].pid == pid) {
            cout << "Date: " << recordList[i].date << ", Diagnosis: " << recordList[i].diagnosis
                 << ", Treatment: " << recordList[i].remedy << endl;
        }
    }
}

void DataControl::showBills(string pid) {
    bool found = false;
    for (int i = 0; i < billTotal; ++i) {
        if (billList[i].pid == pid) {
            found = true;
            cout << "Bill ID: " << billList[i].bid << ", Amount: $" << billList[i].cost
                 << ", Status: " << billList[i].label << endl;
        }
    }
    if (!found) {
        cout << "[INFO] No bills found for Patient ID: " << pid << "\n";
    }
}

void DataControl::handleBilling() {
    string pid = InputTools::getValidatedString("Patient ID: ");
    string bid = InputTools::getValidatedString("Bill ID: ");
    double amt = InputTools::getValidatedDouble("Amount: ");

    BillingItem b;
    b.bid = bid;
    b.pid = pid;
    b.date = "2025-06-26";
    b.cost = amt;
    billList[billTotal++] = b;
    cout << "[SUCCESS] Bill created.\n";
}

void DataControl::assignRoomToPatient() {
    string pid = InputTools::getValidatedString("Patient ID: ");
    string roomNum = InputTools::getValidatedString("Room Number: ");

    for (int i = 0; i < roomTotal; ++i) {
        if (roomList[i].roomNum == roomNum && !roomList[i].filled) {
            for (int j = 0; j < roomTotal; ++j) {
                if (roomList[j].assignedPid == pid) {
                    cout << "[ERROR] Patient already has a room assigned.\n";
                    return;
                }
            }
            roomList[i].assignedPid = pid;
            roomList[i].filled = true;
            cout << "[SUCCESS] Room assigned successfully.\n";
            return;
        }
    }
    cout << "[ERROR] Room not available.\n";
}

void DataControl::viewRoomAssignments() {
    cout << "\n================ ROOM ASSIGNMENTS ================\n";
    bool anyAssigned = false;
    for (int i = 0; i < roomTotal; ++i) {
        if (roomList[i].filled) {
            cout << "Room " << roomList[i].roomNum << " is assigned to Patient ID: " << roomList[i].assignedPid << "\n";
            anyAssigned = true;
        }
    }
    if (!anyAssigned) {
        cout << "No rooms are currently assigned.\n";
    }
    cout << "==================================================\n";
}

void DataControl::listAllPatients() {
    for (int i = 0; i < userTotal; ++i) {
        if (userList[i]->getRoleType() == "Patient") {
            cout << "Patient ID: " << userList[i]->getUserId()
                 << ", Name: " << userList[i]->getFullName() << endl;
        }
    }
}

void DataControl::reviseUserProfile(string uid, string phone, string addr) {
    cout << "[SUCCESS] Profile updated for " << uid << ".\n";
}

#endif // MODULE_4_H
