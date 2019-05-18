#ifndef TOKENS__OPERATOR_TOKEN_H_
#define TOKENS__OPERATOR_TOKEN_H_


#include <functional>

#include "token.h"


class OperatorToken: public Token {

public:
    const std::string REPR_PLAIN;
    const std::string REPR_LATEX;
    const int ARITY;
    const int PRECEDENCE;

public:
    OperatorToken(const std::string& reprPlain, const std::string& reprLaTeX,
                  const int arity, const int precedence);

protected:
    virtual void outputTo(std::ostream& ostream) const override;

public:
    virtual std::string toString() const override;

    OperatorToken& operator=(OperatorToken&) = delete;

    friend class Package;
};

#endif