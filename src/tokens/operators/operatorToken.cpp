#include "operatorToken.h"

OperatorToken::OperatorToken(const int arity, const int absPred,
                             const std::string& idLaTeX,
                             const std::string& idPlain)
    : ARITY{arity}, ABS_PRED{absPred}, ID_LATEX{idLaTeX}, ID_PLAIN{idPlain} {}

void OperatorToken::outputTo(std::ostream& ostream) const {
    ostream << toString();
}

int OperatorToken::getArity() const { return ARITY; }

int OperatorToken::getAbsolutePrecedence() const { return ABS_PRED; }

std::string OperatorToken::toString() const { return ID_PLAIN; }

void OperatorToken::outputTo(std::ostream& ostream) const {
    ostream << toString();
}