#ifndef TOKENS__OPERATORS__OPERATION_H_
#define TOKENS__OPERATORS__OPERATION_H_

#include <memory>

#include "operatorToken.h"

struct OperatorToken::Operation {
   public:
    const NumTypePattern PATTERN;
    const Func operate;
    const int PRECEDENCE;

   private:
    Operation(const Func, const NumTypePattern, const int);

   public:
    unsigned int getArity() const;
    int getPrecedence() const;
    NumTypePattern getMatchPattern() const;

    friend class OperatorToken;
};

#endif