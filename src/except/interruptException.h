#ifndef CALC__EXCEPT__INTERRUPT_EXCEPTION_H_
#define CALC__EXCEPT__INTERRUPT_EXCEPTION_H_

#include <exception>

class InterruptException : public std::exception {
   public:
    const bool FORCE;
    InterruptException(bool force = false) : FORCE{force} {}

    virtual const char* what() const noexcept override {
        return FORCE ? "forced interrupt by user" : "interrupted by user";
    }
};

#endif