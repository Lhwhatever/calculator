#ifndef TOKENS__OPERATORS__BINARY_OPERATOR_TOKEN_H_
#define TOKENS__OPERATORS__BINARY_OPERATOR_TOKEN_H_

#include "../values/valueToken.h"
#include "operatorToken.h"

class BinaryOperatorToken : public OperatorToken {
   public:
    BinaryOperatorToken(const int relativePrecedence,
                        const std::string& identifierLaTeX,
                        const std::string& identifierPlain = "");

   public:
    std::string renderWithArgs(const ValueToken& leftArg,
                               const ValueToken& rightArg) const;
};

#endif