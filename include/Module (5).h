#ifndef MODULE_5_H
#define MODULE_5_H

#include <iostream>
#include <string>
#include <memory>
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
    // Returns raw pointer because DataControl retains ownership
    // User should NOT delete this pointer
    static BaseInterface* verifyAndLogin(const string& email, const string& password);
    
    // Returns unique_ptr - caller takes ownership
    // CRITICAL: Changed from raw pointer to unique_ptr to prevent memory leaks
    static unique_ptr<BaseInterface> fabricate(const string& role);
};

class EngineLoader {
public:
    static void initializeEngine();
};

#endif // MODULE_5_H