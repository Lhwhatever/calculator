#ifndef CALC__TOKENS__OPERATORS__NUM_TYPE_PATTERN_H_
#define CALC__TOKENS__OPERATORS__NUM_TYPE_PATTERN_H_

#include <initializer_list>
#include <memory>
#include <vector>

#include "../values/valueToken.h"

using ValueTP = std::shared_ptr<ValueToken>;
using ValueStack = std::vector<ValueTP>;

struct NumTypePattern final : public std::vector<unsigned short> {
   public:
    NumTypePattern(const unsigned int arity);
    NumTypePattern(const ValueToken::NumType&);
    NumTypePattern(const std::initializer_list<ValueToken::NumTypeR>&);
    NumTypePattern(const NumTypePattern&);
    NumTypePattern(NumTypePattern&&);

   public:
    static NumTypePattern inferFrom(const ValueStack& valueStack,
                                    const unsigned int count);
    void push_back(const ValueToken::NumType&);
    std::string repr() const;
};

#endif