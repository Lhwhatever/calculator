#ifndef TOKENS__VALUES__VALUE_TOKEN_H_
#define TOKENS__VALUES__VALUE_TOKEN_H_

#include "../token.h"

class ValueToken : public Token {
   public:
    enum class ValueType { CONST, VAR };

   public:
    const ValueType VALUE_TYPE;

   public:
    ValueToken(const ValueType valueType = ValueType::CONST)
        : VALUE_TYPE{valueType} {};

    virtual bool isZero() const = 0;
    virtual bool isUnity() const = 0;
};

#endif