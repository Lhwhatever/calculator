#ifndef TOKENS__OPERATOR_TOKEN_H_
#define TOKENS__OPERATOR_TOKEN_H_

#include <memory>
#include <unordered_map>
#include <vector>

#include "../values/valueToken.h"

using ValueTP = std::shared_ptr<ValueToken>;
using ValueStack = std::vector<ValueTP>;
using Operation = void (*)(ValueStack&);
using NumTypeR = std::reference_wrapper<const ValueToken::NumType>;
using NumTypePattern = std::vector<NumTypeR>;
using OperationMap = std::unordered_map<long, const Operation>;

class OperatorToken : public Token {
   public:
    enum Associativity { LEFT_ASSOC, RIGHT_ASSOC };

   private:
    const std::string ID;
    const unsigned int ARITY;
    const int PRECD;
    const Associativity ASSOC;
    OperationMap operations;

   public:
    OperatorToken(const std::string& identifier, unsigned int arity,
                  int precedence, Associativity assoc = LEFT_ASSOC);

   protected:
    virtual void outputTo(std::ostream& ostream) const override;

   public:
    static long getPatternId(const NumTypePattern&);

    virtual std::string toString() const override;
    std::string getIdentifier() const;
    unsigned int getArity() const;
    int getPrecedence() const;
    Associativity getAssociativity() const;

    void bind(const NumTypePattern&, const Operation&);
    void operate(ValueStack& valueStack);

    OperatorToken& operator=(OperatorToken&) = delete;

    friend class Package;
};

#endif