#include "operatorToken.h"

OperatorToken::OperatorToken(const std::string& id) : ID{id}, operations{} {}

void OperatorToken::outputTo(std::ostream& ostream) const {
    ostream << toString();
}

std::string OperatorToken::toString() const { return getIdentifier(); }
std::string OperatorToken::getIdentifier() const { return ID; }

void OperatorToken::bind(const Func func, const NumTypePattern pattern,
                         const int precedence) {
    operations.emplace_back(func, pattern, precedence);
}