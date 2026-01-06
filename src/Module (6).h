#ifndef MODULE_6_H
#define MODULE_6_H

#include <iostream>
#include <string>
#include "Module.h"
#include "Module (2).h"
#include "Module (4).h"  // For DataControl
#include "Module (3).h"  // For AdminUnit, DoctorUnit, FrontDesk, PatientUnit

using namespace std;

// ===== Definitions for AccountGenerator & EngineLoader =====

BaseInterface* AccountGenerator::verifyAndLogin(string email, string password) {
    return DataControl::getInstance()->validateUser(email, password);
}

BaseInterface* AccountGenerator::fabricate(string role) {
    string id = InputTools::getValidatedString("ID: ");
    string name = InputTools::getValidatedString("Name: ");
    string email = InputTools::getValidatedString("Email: ");
    string pass = InputTools::getValidatedString("Password: ");

    if (role == "Admin") return new AdminUnit(id, name, email, pass);
    if (role == "Receptionist") return new FrontDesk(id, name, email, pass);
    if (role == "Doctor") {
        string specialty = InputTools::getValidatedString("Specialization: ");
        return new DoctorUnit(id, name, email, pass, specialty);
    }
    if (role == "Patient") {
        string phone = InputTools::getValidatedString("Phone: ");
        string address = InputTools::getValidatedString("Address: ");
        return new PatientUnit(id, name, email, pass, phone, address);
    }

    return nullptr;
}

void EngineLoader::initializeEngine() {
    DataControl* ref = DataControl::getInstance();

    ref->pushUser(new AdminUnit("A001", "Admin Zain", "admin@hospital.com", "admin123"));
    ref->pushUser(new DoctorUnit("D001", "Dr. Zarak Khan", "zarak@hospital.com", "doc123", "Cardiology"));
    ref->pushUser(new DoctorUnit("D002", "Dr. Zeeshan", "zeeshan@hospital.com", "doc456", "Neurology"));
    ref->pushUser(new FrontDesk("R001", "Shabih Haider", "shabih@hospital.com", "rec123"));
    ref->pushUser(new PatientUnit("P001", "Adan Hashmi", "adan@hospital.com", "adan123", "03001234567", "Street 9, City"));
}

#endif // MODULE_6_H
