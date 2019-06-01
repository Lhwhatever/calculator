#include "funcToken.h"

#include <iostream>

#include "../../except/arityMismatchException.h"
#include "../../except/noOperationException.h"

FuncToken::FuncToken(const std::string& name, const unsigned int arity,
                     const short precLevel,
                     const Precedence::Associativity assoc)
    : Token{Token::CAT_FUNC},
      NAME{name},
      ARITY{arity},
      PREC{precLevel, assoc} {}

bool FuncToken::hasBound(const NumTypePattern pattern) {
    return map.find(pattern) != map.end();
}

bool FuncToken::bind(const NumTypePattern& pattern, const Function& func) {
    if (hasBound(pattern)) return false;
    map.try_emplace(pattern, func);
    return true;
}

void FuncToken::forceBind(const NumTypePattern& pattern, const Function& func) {
    map.insert_or_assign(pattern, func);
}

void FuncToken::unbind(const NumTypePattern& pattern) { map.erase(pattern); }

FuncToken::Errors FuncToken::canOperate(const ValueStack& valueStack) {
    unsigned int size = valueStack.size();
    if (size < ARITY) return ERR_ARITY;
    if (map.find(NumTypePattern::inferFrom(valueStack, ARITY)) == map.end())
        return ERR_TYPE;
    return ERR_NONE;
}

FuncToken::Errors FuncToken::operate(ValueStack& valueStack) {
    unsigned int size = valueStack.size();
    if (size < ARITY) return ERR_ARITY;

    auto pattern{NumTypePattern::inferFrom(valueStack, ARITY)};
    auto it{map.find(pattern)};
    if (it == map.end()) return ERR_TYPE;

    (it->second)(valueStack);
    return ERR_NONE;
}