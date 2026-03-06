#ifndef HMS_ACCOUNTGENERATOR_H
#define HMS_ACCOUNTGENERATOR_H

#include <memory>
#include <string>
#include "BaseInterface.h"

namespace hms {

class AccountGenerator {
public:
    static BaseInterface* verifyAndLogin(const std::string& email, const std::string& password);
    static std::unique_ptr<BaseInterface> fabricate(const std::string& role);
};

} // namespace hms

#endif // HMS_ACCOUNTGENERATOR_H