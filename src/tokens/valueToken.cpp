#include "valueToken.h"

ValueToken::ValueToken(long data)
    : numericType{NumericType::INT}, valueType{ValueType::CONST}, lData{data} {

}

TokenType ValueToken::getTokenType() const {
    return TokenType::VALUE;
}

long ValueToken::getIntegralData() const {
    return lData;
}
