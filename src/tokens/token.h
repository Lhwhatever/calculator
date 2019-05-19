#ifndef CALC__TOKENS__TOKEN__H_
#define CALC__TOKENS__TOKEN__H_

#include <iostream>
#include <string>

#include "../helper/IOutputtable.h"

class Token : public IOutputtable {
   public:
    virtual std::string toString() const = 0;
    operator std::string() const { return toString(); }
};

#endif