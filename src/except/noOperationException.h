#ifndef CALC__EXCEPT__NO_OPERATION_EXCEPTION_H_
#define CALC__EXCEPT__NO_OPERATION_EXCEPTION_H_

#include <exception>
#include <string>

class NoOperationException : public std::exception {
    const std::string MSG;

   public:
    NoOperationException(std::string msg);
    ~NoOperationException();

    virtual const char* what() const noexcept override;
};

#endif