#ifndef CALC__EXCEPT__INVALID_SETTING_EXCEPTION_H_
#define CALC__EXCEPT__INVALID_SETTING_EXCEPTION_H_

#include "simpleStringException.h"

class InvalidSettingException : public SimpleStringException {
   public:
    InvalidSettingException(std::string msg) : SimpleStringException{msg} {}
};

#endif