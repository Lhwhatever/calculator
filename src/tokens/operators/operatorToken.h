#ifndef TOKENS__OPERATOR_TOKEN_H_
#define TOKENS__OPERATOR_TOKEN_H_

#include <functional>
#include <memory>
#include <vector>

#include "../token.h"
#include "operation.h"

class OperatorToken : public Token {
   private:
    const std::string ID;
    std::vector<Operation> operations;

   public:
    OperatorToken(const std::string& identifier);

   protected:
    virtual void outputTo(std::ostream& ostream) const override;

   public:
    virtual std::string toString() const override;
    std::string getIdentifier() const;

    void bind(const Func, const NumTypePattern, const int);
    void operate(ValueStack& valueStack);

    OperatorToken& operator=(OperatorToken&) = delete;

    friend class Package;
};

#endif