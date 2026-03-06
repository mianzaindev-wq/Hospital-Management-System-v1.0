#ifndef HMS_EXCEPTIONS_H
#define HMS_EXCEPTIONS_H

#include <stdexcept>
#include <string>

namespace hms {

class HmsException : public std::runtime_error {
public:
    explicit HmsException(const std::string& msg) : std::runtime_error(msg) {}
};

} // namespace hms

#endif // HMS_EXCEPTIONS_H
