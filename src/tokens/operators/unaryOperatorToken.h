#ifndef TOKENS__OPERATORS__UNARY_OPERATOR_TOKEN_H_
#define TOKENS__OPERATORS__UNARY_OPERATOR_TOKEN_H_

#include "../values/valueToken.h"
#include "operatorToken.h"

class UnaryOperatorToken : public OperatorToken {
   public:
    const bool PREFIXED;  // true if prefixed, false if postfixed

   public:
    UnaryOperatorToken(const int relativePrecedence, const bool prefixed,
                       const std::string& identifierLaTeX,
                       const std::string& identifierPlain = "");

   public:
    bool isPrefixed() const;
    std::string renderWithArgs(const ValueToken&) const;
};

#endif