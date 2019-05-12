#include <string>

#include "valueToken.h"


ValueToken::ValueToken(long data)
    : numericType{NumericType::INT}, valueType{ValueType::CONST}, lData{data} {

}

ValueToken::~ValueToken() {
    
}

TokenType ValueToken::getTokenType() const {
    return TokenType::VALUE;
}

long ValueToken::getIntegralData() const {
    return lData;
}

std::string ValueToken::toString() const {
    return std::to_string(lData);
}

std::ostream& operator<<(std::ostream& ostream, const ValueToken& valueToken) {
    ostream << valueToken.lData;
    return ostream;
}