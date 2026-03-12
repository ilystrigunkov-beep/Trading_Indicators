

#include "Exceptions.h"

namespace core {

    FileException::FileException(const std::string& message): std::runtime_error(message) {}

    ParseException::ParseException(const std::string& message)   : std::runtime_error(message) {}

} // namespace core