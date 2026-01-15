#ifndef MODULE_2_H
#define MODULE_2_H

#include <iostream>
#include <string>

using namespace std;

class BaseInterface {
protected:
    string uid;
    string fullName;
    string loginEmail;
    string loginPass;
    string userType;

public:
    BaseInterface() 
        : uid(""), fullName(""), loginEmail(""), loginPass(""), userType("") {}

    BaseInterface(const string& id, const string& name, const string& email, 
                  const string& pass, const string& role)
        : uid(id), fullName(name), loginEmail(email), loginPass(pass), userType(role) {}

    // CRITICAL: Virtual destructor required for polymorphic deletion
    // Without this, deleting derived classes through base pointer causes memory leaks
    virtual ~BaseInterface() {}

    // Copy operations
    BaseInterface(const BaseInterface& other) 
        : uid(other.uid), fullName(other.fullName), loginEmail(other.loginEmail),
          loginPass(other.loginPass), userType(other.userType) {}

    BaseInterface& operator=(const BaseInterface& other) {
        if (this != &other) {
            uid = other.uid;
            fullName = other.fullName;
            loginEmail = other.loginEmail;
            loginPass = other.loginPass;
            userType = other.userType;
        }
        return *this;
    }

    // Move operations - more efficient than copying for temporaries
    BaseInterface(BaseInterface&& other) noexcept
        : uid(std::move(other.uid)), fullName(std::move(other.fullName)),
          loginEmail(std::move(other.loginEmail)), loginPass(std::move(other.loginPass)),
          userType(std::move(other.userType)) {}

    BaseInterface& operator=(BaseInterface&& other) noexcept {
        if (this != &other) {
            uid = std::move(other.uid);
            fullName = std::move(other.fullName);
            loginEmail = std::move(other.loginEmail);
            loginPass = std::move(other.loginPass);
            userType = std::move(other.userType);
        }
        return *this;
    }

    // Getters - const& avoids unnecessary string copies
    const string& getUserId() const { return uid; }
    const string& getFullName() const { return fullName; }
    const string& getEmailId() const { return loginEmail; }
    const string& getRoleType() const { return userType; }
    const string& getPassword() const { return loginPass; }

    // Setters
    void setFullName(const string& name) { fullName = name; }
    void setEmail(const string& email) { loginEmail = email; }
    void setPassword(const string& pass) { loginPass = pass; }

    virtual bool authenticate(const string& givenEmail, const string& givenPass) const {
        return loginEmail == givenEmail && loginPass == givenPass;
    }

    // Pure virtual - must be implemented by derived classes
    virtual void showDashboard() = 0;

    virtual void viewBills() {
        cout << "[INFO] Bill viewing not available for " << userType << ".\n";
    }

    virtual void displayInfo() const {
        cout << "\n================ USER INFORMATION ================\n";
        cout << "ID       : " << uid << "\n";
        cout << "Name     : " << fullName << "\n";
        cout << "Email    : " << loginEmail << "\n";
        cout << "Role     : " << userType << "\n";
        cout << "==================================================\n";
    }

    // Role checking utilities
    bool isAdmin() const { return userType == "Admin"; }
    bool isDoctor() const { return userType == "Doctor"; }
    bool isPatient() const { return userType == "Patient"; }
    bool isReceptionist() const { return userType == "Receptionist"; }

    // Validates format: Letter followed by digits (e.g., P001, D123)
    bool hasValidIdFormat() const {
        if (uid.empty()) return false;
        if (!isalpha(uid[0])) return false;
        for (size_t i = 1; i < uid.length(); ++i) {
            if (!isdigit(uid[i])) return false;
        }
        return true;
    }

    string getRoleDescription() const {
        if (userType == "Doctor") return "Medical Doctor";
        if (userType == "Patient") return "Hospital Patient";
        if (userType == "Receptionist") return "Front Desk Receptionist";
        if (userType == "Admin") return "System Administrator";
        return "Unknown Role";
    }
};

#endif