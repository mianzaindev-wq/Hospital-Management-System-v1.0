#include "../../include/hms/BaseInterface.h"
#include <iostream>

namespace hms {

BaseInterface::BaseInterface(const std::string& id, const std::string& name,
                             const std::string& email, const std::string& pass,
                             const std::string& role)
    : uid(id), fullName(name), loginEmail(email), loginPass(pass), userType(role) {}

BaseInterface::~BaseInterface() = default;

const std::string& BaseInterface::getUserId() const { return uid; }
const std::string& BaseInterface::getFullName() const { return fullName; }
const std::string& BaseInterface::getEmailId() const { return loginEmail; }
const std::string& BaseInterface::getRoleType() const { return userType; }
const std::string& BaseInterface::getPassword() const { return loginPass; }

void BaseInterface::setFullName(const std::string& name) { fullName = name; }
void BaseInterface::setEmail(const std::string& email) { loginEmail = email; }
void BaseInterface::setPassword(const std::string& pass) { loginPass = pass; }

bool BaseInterface::authenticate(const std::string& givenEmail,
                                 const std::string& givenPass) const {
    return loginEmail == givenEmail && loginPass == givenPass;
}

void BaseInterface::viewBills() {
    std::cout << "[INFO] Bill viewing not available for " << userType << ".\n";
}

void BaseInterface::displayInfo() const {
    std::cout << "\n================ USER INFORMATION ================\n";
    std::cout << "ID       : " << uid << "\n";
    std::cout << "Name     : " << fullName << "\n";
    std::cout << "Email    : " << loginEmail << "\n";
    std::cout << "Role     : " << userType << "\n";
    std::cout << "==================================================\n";
}

bool BaseInterface::isAdmin() const { return userType == "Admin"; }
bool BaseInterface::isDoctor() const { return userType == "Doctor"; }
bool BaseInterface::isPatient() const { return userType == "Patient"; }
bool BaseInterface::isReceptionist() const { return userType == "Receptionist"; }

bool BaseInterface::hasValidIdFormat() const {
    if (uid.empty()) return false;
    if (!isalpha(uid[0])) return false;
    for (size_t i = 1; i < uid.length(); ++i)
        if (!isdigit(uid[i])) return false;
    return true;
}

std::string BaseInterface::getRoleDescription() const {
    if (userType == "Doctor") return "Medical Doctor";
    if (userType == "Patient") return "Hospital Patient";
    if (userType == "Receptionist") return "Front Desk Receptionist";
    if (userType == "Admin") return "System Administrator";
    return "Unknown Role";
}

} // namespace hms
