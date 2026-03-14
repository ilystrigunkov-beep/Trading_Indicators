//
// Created by Aboba on 13.03.2026.
//

#ifndef TRADING_INDICATORS_EXCEPTIONS_H
#define TRADING_INDICATORS_EXCEPTIONS_H


#include <stdexcept>
#include <string>

namespace core {

    class FileException : public std::runtime_error {
    public:
        explicit FileException(const std::string&  message);
    };

    class ParseException : public  std::runtime_error {
    public:
        explicit ParseException(const  std::string& message);
    };

}


#endif //TRADING_INDICATORS_EXCEPTIONS_H
