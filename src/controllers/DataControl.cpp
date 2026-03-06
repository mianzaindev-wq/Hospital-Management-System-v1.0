#include "hms/DataControl.h"
#include "hms/Roles.h"       // bring in DoctorUnit, PatientUnit, etc.
#include "hms/InputTools.h" // header for input validators
#include <algorithm>

namespace hms {

DataControl* DataControl::handler = nullptr;

DataControl::DataControl() {
    roomList.reserve(20);
    for (int i = 1; i <= 20; ++i) {
        RoomSpot spot;
        spot.roomNum = "R" + std::to_string(i);
        spot.filled = false;
        roomList.push_back(spot);
    }
}

DataControl* DataControl::getInstance() {
    if (!handler) {
        handler = new DataControl();
    }
    return handler;
}

void DataControl::destroyInstance() {
    delete handler;
    handler = nullptr;
}

DataControl::~DataControl() = default;

BaseInterface* DataControl::validateUser(const std::string& mail, const std::string& pass) {
    auto it = usersByEmail.find(mail);
    if (it != usersByEmail.end() && it->second->authenticate(mail, pass)) {
        return it->second;
    }
    return nullptr;
}

void DataControl::pushUser(std::unique_ptr<BaseInterface> u) {
    const std::string& id = u->getUserId();
    const std::string& email = u->getEmailId();

    if (usersById.count(id)) {
        throw HmsException("Duplicate ID: " + id);
    }
    if (usersByEmail.count(email)) {
        throw HmsException("Duplicate email: " + email);
    }
    usersByEmail[email] = u.get();
    usersById[id] = std::move(u);
    std::cout << "[SUCCESS] User " << id << " added.\n";
}

void DataControl::registerNewDoctor() {
    std::string id = InputTools::getValidatedString("Doctor ID: ");
    std::string name = InputTools::getValidatedString("Name: ");
    std::string email = InputTools::getValidatedEmail("Email: ");
    std::string pass = InputTools::getValidatedPassword("Password: ");
    std::string spec = InputTools::getValidatedString("Specialization: ");
    auto newDoc = std::make_unique<DoctorUnit>(id, name, email, pass, spec);
    pushUser(std::move(newDoc));
}

void DataControl::registerNewPatient() {
    std::string id = InputTools::getValidatedString("Patient ID: ");
    std::string name = InputTools::getValidatedString("Name: ");
    std::string email = InputTools::getValidatedEmail("Email: ");
    std::string pass = InputTools::getValidatedPassword("Password: ");
    std::string phone = InputTools::getValidatedPhone("Phone: ");
    std::string addr = InputTools::getValidatedString("Address: ");
    auto newPat = std::make_unique<PatientUnit>(id, name, email, pass, phone, addr);
    pushUser(std::move(newPat));
}

void DataControl::registerNewReceptionist() {
    std::string id = InputTools::getValidatedString("Receptionist ID: ");
    std::string name = InputTools::getValidatedString("Name: ");
    std::string email = InputTools::getValidatedEmail("Email: ");
    std::string pass = InputTools::getValidatedPassword("Password: ");
    auto newRec = std::make_unique<FrontDesk>(id, name, email, pass);
    pushUser(std::move(newRec));
}

void DataControl::removeUserById() {
    std::string id = InputTools::getValidatedString("Enter ID to remove: ");
    if (!InputTools::getConfirmation("Are you sure you want to delete user " + id + "?")) {
        std::cout << "[INFO] Deletion cancelled.\n";
        return;
    }
    auto it = usersById.find(id);
    if (it == usersById.end()) {
        std::cout << "[ERROR] User ID not found.\n";
        return;
    }
    usersByEmail.erase(it->second->getEmailId());
    usersById.erase(it);

    // remove appointments etc
    appointmentList.erase(
        std::remove_if(appointmentList.begin(), appointmentList.end(),
            [&id](const AppointmentItem& apt) {
                return apt.pid == id || apt.did == id;
            }),
        appointmentList.end());

    std::cout << "[SUCCESS] User " << id << " removed.\n";
}

void DataControl::displayAppointments() const {
    if (appointmentList.empty()) {
        std::cout << "[INFO] No appointments scheduled.\n";
        return;
    }
    std::cout << "\n================ APPOINTMENTS ================\n";
    for (const auto& apt : appointmentList) {
        std::cout << "ID: " << apt.aid 
                  << " | Patient: " << apt.pid
                  << " | Doctor: " << apt.did
                  << " | Date: " << apt.date
                  << " | Time: " << apt.time
                  << " | Status: " << apt.status << "\n";
    }
    std::cout << "==============================================\n";
}

void DataControl::makeAppointment(const std::string& patientId) {
    std::string docId = InputTools::getValidatedString("Enter Doctor ID: ");
    std::string date = InputTools::getValidatedDate("Date (YYYY-MM-DD): ");
    std::string time = InputTools::getValidatedTime("Time (HH:MM): ");
    for (const auto& apt : appointmentList) {
        if (apt.date == date && apt.time == time &&
            (apt.pid == patientId || apt.did == docId)) {
            throw HmsException("Overlapping appointment detected");
        }
    }
    AppointmentItem a;
    a.aid = "A" + std::to_string(appointmentList.size() + 1);
    a.pid = patientId;
    a.did = docId;
    a.date = date;
    a.time = time;
    a.status = "Scheduled";
    appointmentList.push_back(a);
    std::cout << "[SUCCESS] Appointment booked: " << a.aid << "\n";
}

void DataControl::makeAppointmentManual() {
    std::string pid = InputTools::getValidatedString("Enter Patient ID: ");
    makeAppointment(pid);
}

void DataControl::removeAppointment(const std::string& aid) {
    auto it = std::find_if(appointmentList.begin(), appointmentList.end(),
        [&aid](const AppointmentItem& apt) { return apt.aid == aid; });
    if (it != appointmentList.end()) {
        appointmentList.erase(it);
        std::cout << "[SUCCESS] Appointment cancelled.\n";
    } else {
        std::cout << "[ERROR] Appointment ID not found.\n";
    }
}

void DataControl::inputMedicalRecord(const std::string& docName) {
    std::string pid = InputTools::getValidatedString("Patient ID: ");
    std::string date = InputTools::getValidatedDate("Date (YYYY-MM-DD): ");
    std::string diagnosis = InputTools::getValidatedString("Diagnosis: ");
    std::string treatment = InputTools::getValidatedString("Treatment: ");
    MedicalNote note;
    note.rid = "R" + std::to_string(recordList.size() + 1);
    note.pid = pid;
    note.did = docName;
    note.date = date;
    note.diagnosis = diagnosis;
    note.remedy = treatment;
    recordList.push_back(note);
    std::cout << "[SUCCESS] Medical record added: " << note.rid << "\n";
}

void DataControl::printRecordsForPatient(const std::string& pid) const {
    bool found = false;
    std::cout << "\n================ MEDICAL RECORDS ================\n";
    for (const auto& rec : recordList) {
        if (rec.pid == pid) {
            found = true;
            std::cout << "Record ID: " << rec.rid << "\n";
            std::cout << "Date: " << rec.date << "\n";
            std::cout << "Doctor: " << rec.did << "\n";
            std::cout << "Diagnosis: " << rec.diagnosis << "\n";
            std::cout << "Treatment: " << rec.remedy << "\n";
            std::cout << "-------------------------------------------------\n";
        }
    }
    if (!found) {
        std::cout << "No records found for Patient ID: " << pid << "\n";
    }
    std::cout << "=================================================\n";
}

void DataControl::showBills(const std::string& pid) const {
    bool found = false;
    std::cout << "\n================ BILLING INFORMATION ================\n";
    for (const auto& bill : billList) {
        if (bill.pid == pid) {
            found = true;
            std::cout << "Bill ID: " << bill.bid 
                      << " | Amount: $" << bill.cost
                      << " | Date: " << bill.date
                      << " | Status: " << bill.label << "\n";
        }
    }
    if (!found) {
        std::cout << "No bills found for Patient ID: " << pid << "\n";
    }
    std::cout << "=====================================================\n";
}

void DataControl::handleBilling() {
    std::string pid = InputTools::getValidatedString("Patient ID: ");
    std::string bid = "B" + std::to_string(billList.size() + 1);
    double amt = InputTools::getValidatedDouble("Amount: $", 0.0);
    std::string date = InputTools::getValidatedDate("Date (YYYY-MM-DD): ");
    BillingItem item;
    item.bid = bid;
    item.pid = pid;
    item.date = date;
    item.cost = amt;
    item.label = "Unpaid";
    billList.push_back(item);
    std::cout << "[SUCCESS] Bill created. ID: " << bid << "\n";
}

void DataControl::assignRoomToPatient() {
    std::string pid = InputTools::getValidatedString("Patient ID: ");
    std::string roomNum = InputTools::getValidatedString("Room Number: ");
    for (const auto& room : roomList) {
        if (room.assignedPid == pid) {
            throw HmsException("Patient already has a room");
        }
    }
    for (auto& room : roomList) {
        if (room.roomNum == roomNum) {
            if (room.filled) {
                throw HmsException("Room already occupied");
            }
            room.assignedPid = pid;
            room.filled = true;
            std::cout << "[SUCCESS] Room " << roomNum << " assigned to " << pid << "\n";
            return;
        }
    }
    std::cout << "[ERROR] Room number not found.\n";
}

void DataControl::viewRoomAssignments() const {
    bool any = false;
    std::cout << "\n================ ROOM ASSIGNMENTS ================\n";
    for (const auto& room : roomList) {
        if (room.filled) {
            std::cout << "Room " << room.roomNum << " -> Patient: " << room.assignedPid << "\n";
            any = true;
        }
    }
    if (!any) {
        std::cout << "No rooms currently assigned.\n";
    }
    std::cout << "==================================================\n";
}

void DataControl::listAllPatients() const {
    bool found = false;
    std::cout << "\n================ ALL PATIENTS ================\n";
    for (const auto& pair : usersById) {
        if (pair.second->isPatient()) {
            found = true;
            std::cout << "ID: " << pair.second->getUserId()
                      << " | Name: " << pair.second->getFullName()
                      << " | Email: " << pair.second->getEmailId() << "\n";
        }
    }
    if (!found) std::cout << "No patients registered.\n";
    std::cout << "==============================================\n";
}

void DataControl::listAllUsers() const {
    std::cout << "\n================ ALL USERS ================\n";
    for (const auto& pair : usersById) {
        auto u = pair.second.get();
        std::cout << "ID: " << u->getUserId()
                  << " | Name: " << u->getFullName()
                  << " | Role: " << u->getRoleType()
                  << " | Email: " << u->getEmailId() << "\n";
    }
    std::cout << "Total Users: " << usersById.size() << "\n";
    std::cout << "===========================================\n";
}

void DataControl::reviseUserProfile(const std::string& uid, const std::string& phone,
                                    const std::string& addr) {
    auto it = usersById.find(uid);
    if (it != usersById.end() && it->second->isPatient()) {
        PatientUnit* p = dynamic_cast<PatientUnit*>(it->second.get());
        if (p) {
            p->setPhoneNumber(phone);
            p->setAddress(addr);
            std::cout << "[SUCCESS] Profile updated for " << uid << "\n";
            return;
        }
    }
    std::cout << "[ERROR] Profile update failed.\n";
}

size_t DataControl::getUserCount() const { return usersById.size(); }

} // namespace hms
