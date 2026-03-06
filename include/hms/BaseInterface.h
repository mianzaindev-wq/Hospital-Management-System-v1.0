#ifndef HMS_BASEINTERFACE_H
#define HMS_BASEINTERFACE_H

#include <string>

namespace hms {

class BaseInterface {
protected:
    std::string uid;
    std::string fullName;
    std::string loginEmail;
    std::string loginPass;
    std::string userType;

public:
    BaseInterface() = default;
    BaseInterface(const std::string& id, const std::string& name,
                  const std::string& email, const std::string& pass,
                  const std::string& role);
    virtual ~BaseInterface();

    // copy/move are defaulted (std::string handles it)

    const std::string& getUserId() const;
    const std::string& getFullName() const;
    const std::string& getEmailId() const;
    const std::string& getRoleType() const;
    const std::string& getPassword() const;

    void setFullName(const std::string& name);
    void setEmail(const std::string& email);
    void setPassword(const std::string& pass);

    virtual bool authenticate(const std::string& givenEmail,
                              const std::string& givenPass) const;

    virtual void showDashboard() = 0;
    virtual void viewBills();
    virtual void displayInfo() const;

    bool isAdmin() const;
    bool isDoctor() const;
    bool isPatient() const;
    bool isReceptionist() const;
    bool hasValidIdFormat() const;
    std::string getRoleDescription() const;
};

} // namespace hms

#endif // HMS_BASEINTERFACE_H