#include "floatToken.h"

#include <cmath>
#include <string>

#include "../../math/math.h"

const ValueToken::NumType FloatToken::TYPE_FLOAT{"floating-point"};
long double FloatToken::relEpsilon{1e-8L};
long double FloatToken::absEpsilon{1e-12L};

FloatToken::FloatToken(const long double value,
                       const ValueToken::ValueType valueType)
    : ValueToken{valueType}, value{value} {}

void FloatToken::outputTo(std::ostream& ostream) const { ostream << value; }

double FloatToken::getValue() const { return value; }
void FloatToken::setValue(double newValue) { value = newValue; }

bool FloatToken::isFinite() const { return std::isfinite(value); }
bool FloatToken::isInfinite() const { return std::isinf(value); }
bool FloatToken::isNaN() const { return std::isnan(value); }
bool FloatToken::isNeg() const { return std::signbit(value); }

bool FloatToken::isPosInf() const {
    return std::isinf(value) && !std::signbit(value);
};

bool FloatToken::isNegInf() const {
    return std::isinf(value) && std::signbit(value);
};

const ValueToken::NumType& FloatToken::getNumType() const {
    return FloatToken::TYPE_FLOAT;
}

FloatToken& FloatToken::operator=(const float newValue) {
    value = newValue;
    return *this;
}

FloatToken& FloatToken::operator=(const double newValue) {
    value = newValue;
    return *this;
}

FloatToken& FloatToken::operator=(const long double newVal) {
    value = newVal;
    return *this;
}

FloatToken::operator long double() { return value; }
std::string FloatToken::toString() const { return std::to_string(value); }

bool operator==(const FloatToken& a, const FloatToken& b) {
    return math::approxEquals(a.value, b.value, FloatToken::relEpsilon,
                              FloatToken::absEpsilon);
}

bool operator==(const FloatToken& a, const long double& b) {
    return math::approxEquals(a.value, b, FloatToken::relEpsilon,
                              FloatToken::absEpsilon);
}

bool operator==(const long double& a, const FloatToken& b) {
    return math::approxEquals(a, b.value, FloatToken::relEpsilon,
                              FloatToken::absEpsilon);
}

bool FloatToken::isZero() const {
    return math::approxEquals(value, 0.0L, FloatToken::relEpsilon,
                              FloatToken::absEpsilon);
}

bool FloatToken::isUnity() const {
    return math::approxEquals(value, 1.0L, FloatToken::relEpsilon,
                              FloatToken::absEpsilon);
}

const FloatToken FloatToken::POS_ZERO{+0.0L};
const FloatToken FloatToken::NEG_ZERO{-0.0L};
const FloatToken FloatToken::ONE{1.0L};
const FloatToken FloatToken::POS_INF{
    +std::numeric_limits<long double>::infinity()};
const FloatToken FloatToken::NEG_INF{
    -std::numeric_limits<long double>::infinity()};
