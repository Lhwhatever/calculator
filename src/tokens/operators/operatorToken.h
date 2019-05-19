#ifndef TOKENS__OPERATOR_TOKEN_H_
#define TOKENS__OPERATOR_TOKEN_H_

#include <functional>

#include "token.h"

class OperatorToken : public Token {
   public:
    const int ARITY;
    const int ABS_PRED;  // absolute precedence
    const std::string ID_LATEX;
    const std::string ID_PLAIN;

   protected:
    OperatorToken(const int arity, const int absolutePrecedence,
                  const std::string& identifierLaTeX,
                  const std::string& identifierPlain = "");

   protected:
    virtual void outputTo(std::ostream& ostream) const override;

   public:
    virtual std::string toString() const override;
    int getArity() const;
    int getAbsolutePrecedence() const;

    OperatorToken& operator=(OperatorToken&) = delete;
    virtual void outputTo(std::ostream&) const override;

    friend class Package;
};

#endif