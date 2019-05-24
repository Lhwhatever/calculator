#ifndef CALC__EXCEPT__ARITY_MISMATCH_EXCEPTION_H_
#define CALC__EXCEPT__ARITY_MISMATCH_EXCEPTION_H_

#include <exception>
#include <string>

class ArityMismatchException : public std::exception {
    const std::string ID;
    const int EXPECTED;
    const int RECEIVED;
    const std::string EXTRA;

   public:
    ArityMismatchException(std::string identifier, int argsExpected,
                           int argsReceived, std::string extra = "");
    ~ArityMismatchException();

    virtual const char* what() const noexcept override;
};

#endif