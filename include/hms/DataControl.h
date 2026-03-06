#ifndef HMS_DATACONTROL_H
#define HMS_DATACONTROL_H

#include <vector>
#include <memory>
#include <unordered_map>
#include <string>

#include "BaseInterface.h"
#include "DataModels.h"
#include "Exceptions.h"

namespace hms {

class DataControl {
private:
    // store users in map keyed by id
    std::unordered_map<std::string, std::unique_ptr<BaseInterface>> usersById;
    // quick lookup by email (raw pointer to owned object)
    std::unordered_map<std::string, BaseInterface*> usersByEmail;

    std::vector<AppointmentItem> appointmentList;
    std::vector<MedicalNote> recordList;
    std::vector<BillingItem> billList;
    std::vector<RoomSpot> roomList;

    static DataControl* handler;
    DataControl();
    DataControl(const DataControl&) = delete;
    DataControl& operator=(const DataControl&) = delete;

public:
    static DataControl* getInstance();
    static void destroyInstance();
    ~DataControl();

    // login validation
    BaseInterface* validateUser(const std::string& mail, const std::string& pass);

    // add user (takes ownership); throws if duplicate id/email
    void pushUser(std::unique_ptr<BaseInterface> u);

    // interactive registration helpers
    void registerNewDoctor();
    void registerNewPatient();
    void registerNewReceptionist();
    void removeUserById();

    // appointment management
    void displayAppointments() const;
    void makeAppointment(const std::string& patientId);
    void makeAppointmentManual();
    void removeAppointment(const std::string& aid);

    // medical records
    void inputMedicalRecord(const std::string& docName);
    void printRecordsForPatient(const std::string& pid) const;

    // billing
    void showBills(const std::string& pid) const;
    void handleBilling();

    // room assignments
    void assignRoomToPatient();
    void viewRoomAssignments() const;

    // listings
    void listAllPatients() const;
    void listAllUsers() const;
    void reviseUserProfile(const std::string& uid, const std::string& phone, const std::string& addr);

    // utilities
    size_t getUserCount() const;
};

} // namespace hms

#endif // HMS_DATACONTROL_H
