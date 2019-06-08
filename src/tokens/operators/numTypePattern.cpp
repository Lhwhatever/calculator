#include "numTypePattern.h"
#include <iostream>

NumTypePattern::NumTypePattern(const unsigned int arity)
    : std::vector<unsigned short>(static_cast<std::size_t>(arity)) {}

NumTypePattern::NumTypePattern(
    const std::initializer_list<ValueToken::NumTypeR>& il)
    : NumTypePattern{static_cast<unsigned int>(il.size())} {
    for (auto& e : il) push_back(e.get());
}

NumTypePattern::NumTypePattern(const NumTypePattern& pat)
    : std::vector<unsigned short>{pat} {}

NumTypePattern::NumTypePattern(NumTypePattern&& pat)
    : std::vector<unsigned short>{pat} {}

NumTypePattern NumTypePattern::inferFrom(const ValueStack& valueStack,
                                         const unsigned int count) {
    NumTypePattern pattern{count};
    for (auto s = valueStack.size(), i = s - count; i < s; ++i)
        pattern.push_back(valueStack.at(i)->TYPE_NUM);
    return pattern;
}

void NumTypePattern::push_back(const ValueToken::NumType& numType) {
    // std::vector<unsigned short>::emplace_back(numType.ID); <-- segfault here
}

std::string NumTypePattern::repr() const {
    std::string out{"NumTypePattern("};
    for (auto& e : *this) out += ValueToken::NumType::getById(e).NAME + ", ";
    out.pop_back();
    out.pop_back();
    return out + ')';
}