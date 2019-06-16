#include "calculator/SymbolicOperatorToken.h"

SymbolicOperatorToken::SymbolicOperatorToken(const std::string& sym)
    : symbol{sym} {}

const std::string& SymbolicOperatorToken::getSymbol() const { return symbol; }