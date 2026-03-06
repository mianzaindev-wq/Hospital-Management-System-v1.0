#ifndef HMS_DATAMODELS_H
#define HMS_DATAMODELS_H

#include <string>

namespace hms {

struct AppointmentItem {
    std::string aid;
    std::string pid;
    std::string did;
    std::string date;
    std::string time;
    std::string status;
};

struct MedicalNote {
    std::string rid;
    std::string pid;
    std::string did;
    std::string date;
    std::string diagnosis;
    std::string remedy;
};

struct BillingItem {
    std::string bid;
    std::string pid;
    std::string date;
    std::string label;
    double cost;
};

struct RoomSpot {
    std::string roomNum;
    std::string assignedPid;
    bool filled;
};

} // namespace hms

#endif // HMS_DATAMODELS_H