#ifndef TOKENS_OPERATORTOKEN_H_
#define TOKENS_OPERATORTOKEN_H_


#include <functional>
#include <map>

#include "valueToken.h"


class OperatorToken;


using Functionality = std::function<void(ValueToken*)>;
using OperatorMap = std::map<std::string, OperatorToken*>;


enum class OperatorReprType {
    SYMBOL //, LATEX
};


class OperatorToken: public Token {

public:
    static const OperatorToken PLUS;
    static const OperatorToken MINUS;

    static OperatorMap symbolOperators;

public:
    const std::string REPR;
    const OperatorReprType REPR_TYPE;
    const int ARITY;
    const int PRECEDENCE;
    const Functionality FUNC;

private:
    OperatorToken(const std::string& repr, const OperatorReprType reprType,
                  const int& arity, const int& precedence,
                  const Functionality& functionality);
    virtual ~OperatorToken() override;

public:
    void parse(ValueToken* valueTokens) const;
    virtual TokenType getTokenType() const override;
    virtual std::string toString() const override;
    friend std::ostream& operator<<(std::ostream& ostream, const OperatorToken& token);
};

#endif