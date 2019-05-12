#include "operatorToken.h"


OperatorToken::OperatorToken(
        const std::string& repr, const OperatorReprType reprType,
        const int& arity, const int& precedence,
        const Functionality& functionality
    ): REPR{repr}, REPR_TYPE{reprType},
        ARITY{arity}, PRECEDENCE{precedence}, FUNC{functionality} {
    if(REPR_TYPE == OperatorReprType::SYMBOL)
        OperatorToken::symbolOperators.insert({repr, this});
};

OperatorToken::~OperatorToken() {

}

TokenType OperatorToken::getTokenType() const {
    return TokenType::OPERATOR;
}


std::string OperatorToken::toString() const {
    return REPR;
}


namespace Functionalities {
    void add(ValueToken* valueTokens) {
        valueTokens->lData += (valueTokens + 1)->lData;
    }

    void subtract(ValueToken* valueTokens) {
        valueTokens->lData -= (valueTokens + 1)->lData;
    }
}

std::ostream& operator<<(std::ostream& ostream, const OperatorToken& token) {
    ostream << token.REPR;
    return ostream;
}

OperatorMap OperatorToken::symbolOperators{};

const OperatorToken OperatorToken::PLUS{"+", OperatorReprType::SYMBOL, 2, 1, Functionalities::add};
const OperatorToken OperatorToken::MINUS{"-", OperatorReprType::SYMBOL, 2, 1, Functionalities::subtract};
