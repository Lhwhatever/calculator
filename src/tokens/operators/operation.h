#ifndef TOKENS__OPERATORS__OPERATION_H_
#define TOKENS__OPERATORS__OPERATION_H_

#include <functional>
#include <memory>

#include "../values/valueToken.h"

using ValueTP = std::shared_ptr<ValueToken>;
using ValueStack = std::vector<ValueTP>;
using NumTypeR = std::reference_wrapper<const ValueToken::NumType>;
using NumTypePattern = std::vector<NumTypeR>;

namespace {
using Func = std::function<void(ValueStack&)>;
}

struct Operation {
   public:
    const NumTypePattern PATTERN;
    const Func operate;
    const int PRECEDENCE;

   public:
    Operation(const Func, const NumTypePattern, const int);

   public:
    unsigned int getArity() const;
    int getPrecedence() const;
    NumTypePattern getMatchPattern() const;
};

#endif