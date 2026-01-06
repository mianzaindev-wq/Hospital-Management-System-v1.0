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
    BaseInterface() {
        uid = "";
        fullName = "";
        loginEmail = "";
        loginPass = "";
        userType = "";
    }

    BaseInterface(string id, string name, string email, string pass, string role)
        : uid(id), fullName(name), loginEmail(email), loginPass(pass), userType(role) {}

    virtual ~BaseInterface() {}

    string getUserId() const { return uid; }
    string getFullName() const { return fullName; }
    string getEmailId() const { return loginEmail; }
    string getRoleType() const { return userType; }

    virtual bool authenticate(string givenEmail, string givenPass) {
        return loginEmail == givenEmail && loginPass == givenPass;
    }

    virtual void showDashboard() = 0;

    // Optional: can be overridden in subclasses
    virtual void viewBills() {}
};

#endif
