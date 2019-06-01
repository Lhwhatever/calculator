#include "token.h"

Token::Token(const TokenCategory category) : CATEGORY{category} {}
Token::operator Token::TokenCategory() const { return CATEGORY; }