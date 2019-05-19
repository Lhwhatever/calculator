#include "unaryOperatorToken.h"

UnaryOperatorToken::UnaryOperatorToken(const int relPred, const bool prefixed,
                                       const std::string& idLaTeX,
                                       const std::string& idPlain)
    : OperatorToken{1, relPred + 100, idLaTeX, idPlain}, PREFIXED{prefixed} {}

bool UnaryOperatorToken::isPrefixed() const { return PREFIXED; }

std::string UnaryOperatorToken::renderWithArgs(const ValueToken& value) const {
    if (PREFIXED)
        return toString() + value.toString();
    else
        return value.toString() + toString();
}