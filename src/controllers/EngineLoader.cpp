#include "hms/EngineLoader.h"
#include "hms/DataControl.h"
#include "hms/Roles.h"

namespace hms {

void EngineLoader::initializeEngine() {
    DataControl* ref = DataControl::getInstance();

    try {
        ref->pushUser(std::make_unique<AdminUnit>("A001", "Admin Zain", "admin@hospital.com", "admin123"));
        ref->pushUser(std::make_unique<DoctorUnit>("D001", "Dr. Zarak Khan", "zarak@hospital.com", "doc123", "Cardiology"));
        ref->pushUser(std::make_unique<DoctorUnit>("D002", "Dr. Zeeshan", "zeeshan@hospital.com", "doc456", "Neurology"));
        ref->pushUser(std::make_unique<FrontDesk>("R001", "Shabih Haider", "shabih@hospital.com", "rec123"));
        ref->pushUser(std::make_unique<PatientUnit>("P001", "Adan Hashmi", "adan@hospital.com", "adan123", "03001234567", "Street 9, City"));
    } catch (const std::exception& ex) {
        std::cerr << "[ENGINE] initialization error: " << ex.what() << "\n";
    }
}

} // namespace hms
