#ifndef TOKENS__OPERATOR_TOKEN_H_
#define TOKENS__OPERATOR_TOKEN_H_

#include <map>

#include "../values/valueToken.h"
#include "numTypePattern.h"

using Operation = void (*)(ValueStack&);
using OperationMap = std::map<NumTypePattern, Operation>;

class OperatorToken : public Token {
   public:
    enum Associativity { ASSOC_L, ASSOC_R };

   private:
    std::string ID;
    const unsigned int ARITY;
    const int PRECD;
    const Associativity ASSOC;
    OperationMap operations;

   public:
    OperatorToken(const std::string identifier, const unsigned int arity,
                  const int precedence, Associativity assoc);

    OperatorToken(const OperatorToken& tok, const std::string& alias);
    OperatorToken(const OperatorToken& tok, const std::string& alias,
                  const int precedence);

    OperatorToken(const OperatorToken& tok) = delete;

   protected:
    virtual void outputTo(std::ostream& ostream) const override;

   public:
    virtual std::string toString() const override;
    const std::string& getIdentifier() const;
    void setIdentifier(const std::string&);

    unsigned int getArity() const;
    int getPrecedence() const;
    Associativity getAssociativity() const;

    void bind(const NumTypePattern&, const Operation&);
    void operate(ValueStack& valueStack);

    OperatorToken& operator=(OperatorToken&) = delete;

    friend class Package;
};

#endif