#ifndef CALC__EXCEPT__ARITY_MISMATCH_EXCEPTION_H_
#define CALC__EXCEPT__ARITY_MISMATCH_EXCEPTION_H_

#include "syntaxException.h"

class ArityMismatchException : public SyntaxException {
    const std::string ID;
    const unsigned int EXPECTED;
    const unsigned int RECEIVED;

   public:
    ArityMismatchException(std::string identifier, unsigned int argsExpected,
                           unsigned int argsReceived, std::string extra = "");
    ~ArityMismatchException();

    virtual const char* what() const noexcept override;
};

#endif