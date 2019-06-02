#ifndef CALC__EXCEPT__SIMPLE_STRING_EXCEPTION_H_
#define CALC__EXCEPT__SIMPLE_STRING_EXCEPTION_H_

#include <exception>
#include <string>

class SimpleStringException : public std::exception {
   protected:
    const std::string MSG;

    SimpleStringException(std::string msg = "") : MSG{msg} {}
    ~SimpleStringException() {}

   public:
    virtual const char* what() const noexcept override { return MSG.c_str(); }
};

#endif