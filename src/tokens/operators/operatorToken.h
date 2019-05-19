#ifndef TOKENS__OPERATOR_TOKEN_H_
#define TOKENS__OPERATOR_TOKEN_H_

#include <functional>
#include <vector>

#include "../token.h"
#include "../values/valueToken.h"

using ValueTR = std::reference_wrapper<ValueToken>;
using ValueStack = std::vector<ValueTR>;
using NumTypePattern = std::vector<std::reference_wrapper<ValueToken::NumType>>;

namespace {
using Func = std::function<void(ValueStack)>;
}

class OperatorToken : public Token {
   public:
    struct Operation;

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

    void registerOperation(const Func, const NumTypePattern, const int);

    OperatorToken& operator=(OperatorToken&) = delete;

    friend class Package;
};

#endif