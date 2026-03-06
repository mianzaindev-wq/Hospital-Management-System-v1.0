#include "hms/AccountGenerator.h"
#include "hms/DataControl.h"
#include "hms/Roles.h"
#include "hms/InputTools.h"

namespace hms {

BaseInterface* AccountGenerator::verifyAndLogin(const std::string& email, const std::string& password) {
    return DataControl::getInstance()->validateUser(email, password);
}

std::unique_ptr<BaseInterface> AccountGenerator::fabricate(const std::string& role) {
    std::string id = InputTools::getValidatedString("ID: ");
    std::string name = InputTools::getValidatedString("Name: ");
    std::string email = InputTools::getValidatedEmail("Email: ");
    std::string pass = InputTools::getValidatedPassword("Password: ");

    if (role == "Admin")
        return std::make_unique<AdminUnit>(id, name, email, pass);
    if (role == "Receptionist")
        return std::make_unique<FrontDesk>(id, name, email, pass);
    if (role == "Doctor") {
        std::string spec = InputTools::getValidatedString("Specialization: ");
        return std::make_unique<DoctorUnit>(id, name, email, pass, spec);
    }
    if (role == "Patient") {
        std::string phone = InputTools::getValidatedPhone("Phone: ");
        std::string addr = InputTools::getValidatedString("Address: ");
        return std::make_unique<PatientUnit>(id, name, email, pass, phone, addr);
    }

    return nullptr;
}

} // namespace hms
