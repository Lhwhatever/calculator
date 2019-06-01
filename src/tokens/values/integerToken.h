#ifndef TOKENS__VALUES__INTEGER_TOKEN_H_
#define TOKENS__VALUES__INTEGER_TOKEN_H_

#include "valueToken.h"

class IntegerToken : public ValueToken {
    long long value;

   public:
    static const IntegerToken ZERO;
    static const IntegerToken ONE;
    static const NumType& TYPE_INTEGER;
    static const long long MAX;
    static const long long MIN;

   public:
    IntegerToken(const long long value,
                 const ValueToken::ValueType = ValueToken::ASSIGNABLE);

   public:
    long long getValue() const;
    IntegerToken& operator=(const long long value);
    operator long long();
};

#endif