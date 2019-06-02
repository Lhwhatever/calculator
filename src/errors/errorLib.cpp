#include "errorLib.h"

InsufficientArgumentsError::InsufficientArgumentsError(
    const std::string& name, const unsigned int expected,
    const unsigned int received)
    : Error{"InsufficientArguments",
            "operator/function " + name + " expected " +
                std::to_string(expected) + " arguments but only received " +
                std::to_string(received)} {}

WrongArgumentTypeError::WrongArgumentTypeError(const std::string& name,
                                               const NumTypePattern& p)
    : Error{"WrongArgumentType",
            "operator/function " + name + " cannot operate on " + p.repr()} {}

DataOutOfLimitError::DataOutOfLimitError(const std::string& type,
                                         const std::string& value,
                                         const std::string& limit)
    : Error{"DataOutOfLimit",
            "type " + type + " cannot store value " + value +
                (limit == "" ? "" : "(limit is " + limit + ")")} {}

UnknownOperatorError::UnknownOperatorError(const std::string& id)
    : Error{"UnknownOperator", "unknown operator " + id} {}