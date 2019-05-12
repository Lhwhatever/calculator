#ifndef VALUETOKEN_H
#define VALUETOKEN_H


#include "token.h"

class ValueToken;


enum class NumericType {
    INT
};

enum class ValueType {
    CONST, VAR
};

namespace Functionalities {
    void add(ValueToken *valueTokens);
    void subtract(ValueToken *valueTokens);
}

class ValueToken: public Token {
private:
    NumericType numericType;
    ValueType valueType;
    long lData;

public:
    ValueToken(long data);

public:
    virtual TokenType getTokenType() const override;
    long getIntegralData() const;
    operator std::string() const {
        return std::to_string(lData);
    }

    friend void Functionalities::add(ValueToken *valueTokens);
    friend void Functionalities::subtract(ValueToken *valueTokens);
};


#endif