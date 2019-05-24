#include "operatorToken.h"

#include <functional>

#include "../../except/arityMismatchException.h"
#include "../../except/noOperationException.h"

OperatorToken::OperatorToken(const std::string& id, unsigned int arity,
                             int precd)
    : ID{id}, ARITY{arity}, PRECD{precd}, operations{} {}

void OperatorToken::outputTo(std::ostream& ostream) const {
    ostream << toString();
}

std::string OperatorToken::toString() const { return getIdentifier(); }
std::string OperatorToken::getIdentifier() const { return ID; }

long OperatorToken::getPatternId(const NumTypePattern& pattern) {
    long patternId{0};
    for (auto it = pattern.cbegin(), end = pattern.end(); it != end; ++it)
        patternId = (patternId << 8) + it->get().getId();
    return patternId;
}

void OperatorToken::bind(const NumTypePattern& pattern, const Operation& oper) {
    if (pattern.size() != ARITY)
        throw ArityMismatchException(
            ID, ARITY, pattern.size(),
            "when binding new Operation to OperatorToken");

    operations.try_emplace(getPatternId(pattern), oper);
}

void OperatorToken::operate(ValueStack& values) {
    auto size{values.size()};
    if (size < ARITY)
        throw ArityMismatchException(ID, ARITY, size,
                                     "when executing operation");

    long patternId{0};
    for (int i = size - ARITY, s = size; i < s; ++i)
        patternId = (patternId << 8) + values[i]->getNumType().getId();

    if (operations.find(patternId) == operations.end())
        throw NoOperationException("no operation could be found");

    operations.at(patternId)(values);
}