#include "token.h"


TokenType Token::getTokenType() const {
    return TokenType::UNDEFINED;
}

std::ostream& operator<<(std::ostream& ostream, const Token& token) {
    ostream << token.toString();
    return ostream;
}