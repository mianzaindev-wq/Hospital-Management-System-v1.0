#include "hms/Roles.h"
#include "hms/DataControl.h"

namespace hms {

// DoctorUnit
DoctorUnit::DoctorUnit(const std::string& id, const std::string& name,
                       const std::string& email, const std::string& pass,
                       const std::string& spec)
    : BaseInterface(id, name, email, pass, "Doctor"), specialization(spec) {}
DoctorUnit::~DoctorUnit() = default;
const std::string& DoctorUnit::getSpecialization() const { return specialization; }
void DoctorUnit::setSpecialization(const std::string& spec) { specialization = spec; }

void DoctorUnit::showDashboard() {
    int choice;
    do {
        hms::InputTools::clearScreen();
        std::cout << "\n================== DOCTOR DASHBOARD ==================\n";
        std::cout << "[1] View My Schedule\n";
        std::cout << "[2] Add Medical Record\n";
        std::cout << "[3] View Patient Records\n";
        std::cout << "[4] View Bills\n";
        std::cout << "[5] Logout\n";
        std::cout << "======================================================\n";
        choice = hms::InputTools::getValidatedInteger("Select option: ", 1, 5);
        try {
            switch (choice) {
                case 1:
                    DataControl::getInstance()->displayAppointments();
                    break;
                case 2:
                    DataControl::getInstance()->inputMedicalRecord(fullName);
                    break;
                case 3: {
                    std::string pid = hms::InputTools::getValidatedString("Enter Patient ID: ");
                    DataControl::getInstance()->printRecordsForPatient(pid);
                    break;
                }
                case 4: {
                    std::string pid = hms::InputTools::getValidatedString("Enter Patient ID: ");
                    DataControl::getInstance()->showBills(pid);
                    break;
                }
                case 5:
                    std::cout << "[INFO] Logging out...\n";
                    break;
            }
        } catch (const HmsException& ex) {
            std::cout << "[ERROR] " << ex.what() << "\n";
        }
    } while (choice != 5);
}

void DoctorUnit::displayInfo() const {
    BaseInterface::displayInfo();
    std::cout << "Specialization: " << specialization << "\n";
    std::cout << "==================================================\n";
}

// PatientUnit
PatientUnit::PatientUnit(const std::string& id, const std::string& name,
                         const std::string& email, const std::string& pass,
                         const std::string& phone, const std::string& addr)
    : BaseInterface(id, name, email, pass, "Patient"),
      phoneNumber(phone), address(addr) {}
PatientUnit::~PatientUnit() = default;
const std::string& PatientUnit::getPhoneNumber() const { return phoneNumber; }
const std::string& PatientUnit::getAddress() const { return address; }
void PatientUnit::setPhoneNumber(const std::string& phone) { phoneNumber = phone; }
void PatientUnit::setAddress(const std::string& addr) { address = addr; }

void PatientUnit::showDashboard() {
    int choice;
    do {
        hms::InputTools::clearScreen();
        std::cout << "\n================== PATIENT DASHBOARD =================\n";
        std::cout << "[1] Book Appointment\n";
        std::cout << "[2] View Appointments\n";
        std::cout << "[3] Cancel Appointment\n";
        std::cout << "[4] View Medical Records\n";
        std::cout << "[5] View Bills\n";
        std::cout << "[6] Update Profile\n";
        std::cout << "[7] Logout\n";
        std::cout << "======================================================\n";
        choice = hms::InputTools::getValidatedInteger("Select option: ", 1, 7);
        try {
            switch (choice) {
                case 1:
                    DataControl::getInstance()->makeAppointment(uid);
                    break;
                case 2:
                    DataControl::getInstance()->displayAppointments();
                    break;
                case 3: {
                    std::string aid = hms::InputTools::getValidatedString("Enter Appointment ID to cancel: ");
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
                    std::string newPhone = hms::InputTools::getValidatedPhone("Enter new phone: ");
                    std::string newAddr = hms::InputTools::getValidatedString("Enter new address: ");
                    setPhoneNumber(newPhone);
                    setAddress(newAddr);
                    DataControl::getInstance()->reviseUserProfile(uid, newPhone, newAddr);
                    std::cout << "[SUCCESS] Profile updated.\n";
                    break;
                }
                case 7:
                    std::cout << "[INFO] Logging out...\n";
                    break;
            }
        } catch (const HmsException& ex) {
            std::cout << "[ERROR] " << ex.what() << "\n";
        }
    } while (choice != 7);
}

void PatientUnit::displayInfo() const {
    BaseInterface::displayInfo();
    std::cout << "Phone    : " << phoneNumber << "\n";
    std::cout << "Address  : " << address << "\n";
    std::cout << "==================================================\n";
}

// FrontDesk
FrontDesk::FrontDesk(const std::string& id, const std::string& name,
                     const std::string& email, const std::string& pass)
    : BaseInterface(id, name, email, pass, "Receptionist") {}
FrontDesk::~FrontDesk() = default;

void FrontDesk::showDashboard() {
    int choice;
    do {
        hms::InputTools::clearScreen();
        std::cout << "\n================ RECEPTIONIST DASHBOARD ==============\n";
        std::cout << "[1] Register New Patient\n";
        std::cout << "[2] Schedule Appointment\n";
        std::cout << "[3] Assign Room\n";
        std::cout << "[4] Handle Payment\n";
        std::cout << "[5] View All Patients\n";
        std::cout << "[6] View Bills\n";
        std::cout << "[7] View Room Assignments\n";
        std::cout << "[8] Logout\n";
        std::cout << "======================================================\n";
        choice = hms::InputTools::getValidatedInteger("Choose option: ", 1, 8);
        try {
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
                    std::string pid = hms::InputTools::getValidatedString("Enter Patient ID: ");
                    DataControl::getInstance()->showBills(pid);
                    break;
                }
                case 7:
                    DataControl::getInstance()->viewRoomAssignments();
                    break;
                case 8:
                    std::cout << "[INFO] Logging out...\n";
                    break;
            }
        } catch (const HmsException& ex) {
            std::cout << "[ERROR] " << ex.what() << "\n";
        }
    } while (choice != 8);
}

// AdminUnit
AdminUnit::AdminUnit(const std::string& id, const std::string& name,
                     const std::string& email, const std::string& pass)
    : BaseInterface(id, name, email, pass, "Admin") {}
AdminUnit::~AdminUnit() = default;

void AdminUnit::showDashboard() {
    int choice;
    do {
        hms::InputTools::clearScreen();
        std::cout << "\n=================== ADMIN DASHBOARD ==================\n";
        std::cout << "[1] Add Doctor\n";
        std::cout << "[2] Add Receptionist\n";
        std::cout << "[3] Remove Staff\n";
        std::cout << "[4] View Appointments\n";
        std::cout << "[5] View Patient Bills\n";
        std::cout << "[6] View Room Assignments\n";
        std::cout << "[7] View All Users\n";
        std::cout << "[8] Logout\n";
        std::cout << "======================================================\n";
        choice = hms::InputTools::getValidatedInteger("Select action: ", 1, 8);
        try {
            switch (choice) {
                case 1:
                    DataControl::getInstance()->registerNewDoctor();
                    break;
                case 2:
                    DataControl::getInstance()->registerNewReceptionist();
                    break;
                case 3: {
                    std::string id = hms::InputTools::getValidatedString("Enter user ID to remove: ");
                    DataControl::getInstance()->removeUserById();
                    break;
                }
                case 4:
                    DataControl::getInstance()->displayAppointments();
                    break;
                case 5: {
                    std::string pid = hms::InputTools::getValidatedString("Enter patient ID: ");
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
                    std::cout << "[INFO] Logging out...\n";
                    break;
            }
        } catch (const HmsException& ex) {
            std::cout << "[ERROR] " << ex.what() << "\n";
        }
    } while (choice != 8);
}

} // namespace hms
