#ifndef TOKENS__VALUES__FLOAT_TOKEN_H_
#define TOKENS__VALUES__FLOAT_TOKEN_H_

#include "valueToken.h"

class FloatToken : public ValueToken {
    long double value;

   public:
    static const FloatToken POS_ZERO;
    static const FloatToken NEG_ZERO;
    static const FloatToken POS_INF;
    static const FloatToken NEG_INF;
    static const FloatToken ONE;

    static const NumType& TYPE_FLOAT;
    static long double absEpsilon;
    static long double relEpsilon;

   public:
    FloatToken(const long double value,
               const ValueToken::ValueType = ValueToken::ASSIGNABLE);

   public:
    double getValue() const;
    void setValue(const double);

    bool isFinite() const;
    bool isPosInf() const;
    bool isNegInf() const;
    bool isInfinite() const;
    bool isNaN() const;
    bool isNeg() const;

    FloatToken& operator=(const float value);
    FloatToken& operator=(const double value);
    FloatToken& operator=(const long double value);
    operator long double();

    friend bool operator==(const FloatToken&, const FloatToken&);
    friend bool operator==(const FloatToken&, const long double& val);
    friend bool operator==(const long double& val, const FloatToken&);
};

#endif