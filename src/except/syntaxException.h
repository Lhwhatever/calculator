#ifndef CALC__EXCEPT__SYNTAX_EXCEPTION_H_
#define CALC__EXCEPT__SYNTAX_EXCEPTION_H_

#include "simpleStringException.h"

class SyntaxException : public SimpleStringException {
   public:
    SyntaxException(std::string str = "")
        : SimpleStringException{"unexpected token " + str} {};
};

#endif