#ifndef TOKENS__OPERATOR_TOKEN_H_
#define TOKENS__OPERATOR_TOKEN_H_

#include <functional>
#include <memory>
#include <vector>

#include "../token.h"
#include "operation.h"

class OperatorToken : public Token {
   private:
    const std::string ID_LATEX;
    const std::string ID_PLAIN;
    std::vector<Operation> operations;

   public:
    OperatorToken(const std::string& identifierLaTeX,
                  const std::string& identifierPlain = "");

   protected:
    virtual void outputTo(std::ostream& ostream) const override;

   public:
    virtual std::string toString() const override;
    std::string getLaTeXIdentifier() const;
    std::string getPlainIdentifier() const;

    void bind(const Func, const NumTypePattern, const int);
    void operate(ValueStack& valueStack);

    OperatorToken& operator=(OperatorToken&) = delete;

    friend class Package;
};

#endif