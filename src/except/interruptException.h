#ifndef CALC__EXCEPT__INTERRUPT_EXCEPTION_H_
#define CALC__EXCEPT__INTERRUPT_EXCEPTION_H_

#include <exception>

class InterruptException : public std::exception {
   public:
    virtual const char* what() const noexcept override {
        return "interrupted by user";
    }
};

#endif