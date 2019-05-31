#ifndef CALC__TOKENS__OPERATORS__NUM_TYPE_PATTERN_H_
#define CALC__TOKENS__OPERATORS__NUM_TYPE_PATTERN_H_

#include <initializer_list>
#include <memory>
#include <vector>

#include "../values/valueToken.h"

using ValueTP = std::shared_ptr<ValueToken>;
using ValueStack = std::vector<ValueTP>;
using NumTypeR = std::reference_wrapper<const ValueToken::NumType>;

struct NumTypePattern : public std::vector<unsigned short> {
   public:
    NumTypePattern(const unsigned long arity);
    NumTypePattern(const ValueToken::NumType&);
    NumTypePattern(const std::initializer_list<NumTypeR>&);

    void push_back(const ValueToken::NumType&);
};

#endif