#include "operatorToken.h"


TokenType OperatorToken::getTokenType() const {
    return TokenType::OPERATOR;
}


namespace Functionalities {
    void add(ValueToken *valueTokens) {
        ValueToken *ptr = valueTokens;
        ptr->lData += (++ptr)->lData;
    }

    void subtract(ValueToken *valueTokens) {
        ValueToken *ptr = valueTokens;
        ptr->lData -= (++ptr)->lData;
    }
}


const OperatorToken OperatorToken::PLUS{"+", 2, 1, Functionalities::add};
const OperatorToken OperatorToken::MINUS{"-", 2, 1, Functionalities::subtract};
