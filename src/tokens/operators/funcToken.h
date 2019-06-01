#ifndef TOKENS__FUNCTIONAL_TOKEN_H_
#define TOKENS__FUNCTIONAL_TOKEN_H_

#include <map>
#include <string>

#include "../token.h"
#include "numTypePattern.h"
#include "precedence.h"

using Function = void (*)(ValueStack&);
using FunctionMap = std::map<NumTypePattern, Function>;

class FuncToken : public Token {
    FunctionMap map;
    const std::string& NAME;

   public:
    const unsigned int ARITY;
    const Precedence PREC;

    enum Errors { ERR_NONE, ERR_ARITY, ERR_TYPE };

   public:
    FuncToken(const std::string& name, const unsigned int arity,
              const short precLevel, const Precedence::Associativity assoc);

    FuncToken(FuncToken&) = delete;  // can't copy

   public:
    bool hasBound(const NumTypePattern pattern);
    bool bind(const NumTypePattern& pattern, const Function& func);
    void forceBind(const NumTypePattern& pattern, const Function& func);
    void unbind(const NumTypePattern& pattern);

    Errors canOperate(const ValueStack& valueStack);
    void operate(ValueStack& valueStack);

    FuncToken& operator=(FuncToken&) = delete;  // can't copy-assign

    friend class Package;
};

#endif