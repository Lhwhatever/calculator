#ifndef TOKEN_H
#define TOKEN_H


#include <iostream>
#include <string>
#include <vector>


enum class TokenType {
    UNDEFINED, VALUE, OPERATOR
};

class Token {
public:
    virtual ~Token() {};

public:
    virtual TokenType getTokenType() const;
    virtual std::string toString() const = 0;

    friend std::ostream& operator<<(std::ostream& ostream, const Token& token);
};

#endif