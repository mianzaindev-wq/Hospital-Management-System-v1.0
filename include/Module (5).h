#ifndef MODULE_5_H
#define MODULE_5_H

#include <iostream>
#include <string>
#include "Module.h"
#include "Module (2).h"

using namespace std;

// Forward declarations
class DataControl;
class AdminUnit;
class DoctorUnit;
class FrontDesk;
class PatientUnit;

class AccountGenerator {
public:
    static BaseInterface* verifyAndLogin(string email, string password);
    static BaseInterface* fabricate(string role);
};

class EngineLoader {
public:
    static void initializeEngine();
};

#endif
