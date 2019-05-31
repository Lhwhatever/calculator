#include "numTypePattern.h"

NumTypePattern::NumTypePattern(const unsigned long arity)
    : std::vector<unsigned short>(static_cast<std::size_t>(arity)) {}

NumTypePattern::NumTypePattern(const std::initializer_list<NumTypeR>& il)
    : NumTypePattern{il.size()} {
    int i = 0;
    for (auto& e : il) push_back(e.get());
}

void NumTypePattern::push_back(const ValueToken::NumType& numType) {
    std::vector<unsigned short>::push_back(numType.getId());
}