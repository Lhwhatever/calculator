#ifndef CALC__EXCEPT__DATA_OUT_OF_LIMIT_EXCEPTION_H_
#define CALC__EXCEPT__DATA_OUT_OF_LIMIT_EXCEPTION_H_

#include <exception>
#include <string>

class DataOutOfLimitException : public std::exception {
    const std::string TYPE;
    const std::string LIMIT;
    const std::string VALUE;

   public:
    DataOutOfLimitException(const std::string& typeAsString,
                            const std::string& limitAsString,
                            const std::string& valueAsString = "");

    virtual const char* what() const noexcept override;
};

#endif