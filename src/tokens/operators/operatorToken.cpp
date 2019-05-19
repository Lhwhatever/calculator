#include "operatorToken.h"

OperatorToken::OperatorToken(const std::string& idLaTeX,
                             const std::string& idPlain)
    : ID_LATEX{idLaTeX}, ID_PLAIN{idPlain}, operations{} {}

void OperatorToken::outputTo(std::ostream& ostream) const {
    ostream << toString();
}

std::string OperatorToken::toString() const { return getPlainIdentifier(); }
std::string OperatorToken::getLaTeXIdentifier() const { return ID_LATEX; }
std::string OperatorToken::getPlainIdentifier() const { return ID_PLAIN; }

void OperatorToken::registerOperation(const Func func,
                                      const NumTypePattern pattern,
                                      const int precedence) {
    operations.emplace_back(func, pattern, precedence);
}