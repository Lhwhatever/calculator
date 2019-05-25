#ifndef CALC__EXCEPT__NO_OPERATION_EXCEPTION_H_
#define CALC__EXCEPT__NO_OPERATION_EXCEPTION_H_

#include <exception>
#include <string>

class NoOperationException : public SimpleStringException {
   public:
    NoOperationException(std::string msg) : SimpleStringException{msg} {}
};

#endif