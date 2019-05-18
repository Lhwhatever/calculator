#include "operatorToken.h"


OperatorToken::OperatorToken(
    const std::string& reprPlain, const std::string& reprLaTeX,
    const int arity, const int precedence):
        REPR_PLAIN{reprPlain}, REPR_LATEX{reprLaTeX},
        ARITY{arity}, PRECEDENCE{precedence} {}


void OperatorToken::outputTo(std::ostream& ostream) const {
    ostream << toString();
}

std::string OperatorToken::toString() const {
    return REPR_PLAIN;
}

//const OperatorToken OperatorToken::PLUS{"+", OperatorReprType::SYMBOL, 2, 1, Functionalities::add};
//const OperatorToken OperatorToken::MINUS{"-", OperatorReprType::SYMBOL, 2, 1, Functionalities::subtract};
