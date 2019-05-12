#ifndef TOKEN_H
#define TOKEN_H


#include <iostream>
#include <string>
#include <vector>


enum class TokenType {
    UNDEFINED, VALUE, OPERATOR
};

class Token {

    virtual TokenType getTokenType() const;

};

#endif