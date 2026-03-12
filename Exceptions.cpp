//
// Created by Aboba on 13.03.2026.
//

#include "Exceptions.h"
namespace core {

    FileException::FileException(const std::string& message)  : std::runtime_error(message) {}

    ParseException::ParseException(const std::string& message)  : std::runtime_error(message) {}

}