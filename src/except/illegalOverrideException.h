#ifndef CALC__EXCEPT__ILLEGAL_OVERRIDE_EXCEPTION_H_
#define CALC__EXCEPT__ILLEGAL_OVERRIDE_EXCEPTION_H_

#include "simpleStringException.h"

class IllegalOverrideException : public SimpleStringException {
   public:
    IllegalOverrideException(const std::string& item)
        : SimpleStringException("cannot override or replace existing " +
                                item){};
};

#endif