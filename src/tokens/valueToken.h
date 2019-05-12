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
    void add(ValueToken* valueTokens);
    void subtract(ValueToken* valueTokens);
}

class ValueToken: public Token {
private:
    NumericType numericType;
    ValueType valueType;
    long lData;

public:
    ValueToken(long data);
    virtual ~ValueToken() override;

public:
    virtual TokenType getTokenType() const override;
    long getIntegralData() const;
    virtual std::string toString() const override;

    friend std::ostream& operator<<(std::ostream& ostream, const ValueToken& valueToken);

    friend void Functionalities::add(ValueToken* valueTokens);
    friend void Functionalities::subtract(ValueToken* valueTokens);
};


#endif