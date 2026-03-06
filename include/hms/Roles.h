#ifndef HMS_ROLES_H
#define HMS_ROLES_H

#include "BaseInterface.h"
#include "InputTools.h"
#include "DataControl.h" // forward declarations may also suffice

namespace hms {

class DoctorUnit : public BaseInterface {
private:
    std::string specialization;
public:
    DoctorUnit(const std::string& id, const std::string& name,
               const std::string& email, const std::string& pass,
               const std::string& spec);
    virtual ~DoctorUnit();

    const std::string& getSpecialization() const;
    void setSpecialization(const std::string& spec);

    void showDashboard() override;
    void displayInfo() const override;
};

class PatientUnit : public BaseInterface {
private:
    std::string phoneNumber;
    std::string address;
public:
    PatientUnit(const std::string& id, const std::string& name,
                const std::string& email, const std::string& pass,
                const std::string& phone, const std::string& addr);
    virtual ~PatientUnit();
    const std::string& getPhoneNumber() const;
    const std::string& getAddress() const;
    void setPhoneNumber(const std::string& phone);
    void setAddress(const std::string& addr);

    void showDashboard() override;
    void displayInfo() const override;
};

class FrontDesk : public BaseInterface {
public:
    FrontDesk(const std::string& id, const std::string& name,
              const std::string& email, const std::string& pass);
    virtual ~FrontDesk();
    void showDashboard() override;
};

class AdminUnit : public BaseInterface {
public:
    AdminUnit(const std::string& id, const std::string& name,
              const std::string& email, const std::string& pass);
    virtual ~AdminUnit();
    void showDashboard() override;
};

} // namespace hms

#endif // HMS_ROLES_H