#ifndef OPERATOR_H
#define OPERATOR_H


#include <functional>
#include "valueToken.h"


using Functionality = std::function<void(ValueToken *)>;


class OperatorToken: public Token {

public:
    static const OperatorToken PLUS;
    static const OperatorToken MINUS;

public:
    const int ARITY;
    const int PRECEDENCE;
    const std::string REPR;
    const Functionality FUNC;

private:
    OperatorToken(const std::string &repr, const int &arity, const int &precedence,
                  const Functionality functionality)
        : REPR{repr}, ARITY{arity}, PRECEDENCE{precedence}, FUNC{functionality} {

    }

public:
    void parse(ValueToken *valueTokens) const;
    virtual TokenType getTokenType() const override;
};

#endif