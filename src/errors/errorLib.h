#ifndef CALC__ERROR__ERROR_LIB_H_
#define CALC__ERROR__ERROR_LIB_H_

#include "../tokens/operators/numTypePattern.h"
#include "error.h"

struct InsufficientArgumentsError : public Error {
    InsufficientArgumentsError(const std::string& name,
                               const unsigned int expected,
                               const unsigned int received);
};

struct WrongArgumentTypeError : public Error {
    WrongArgumentTypeError(const std::string& name, const NumTypePattern&);
};

struct DataOutOfLimitError : public Error {
    DataOutOfLimitError(const std::string& type, const std::string& value = "",
                        const std::string& limit = "");
};

struct UnknownOperatorError : public Error {
    UnknownOperatorError(const std::string& identifier);
};

#endif