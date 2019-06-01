#include "integerToken.h"

#include <limits>

const ValueToken::NumType& IntegerToken::TYPE_INTEGER{"Integer"};

IntegerToken::IntegerToken(const long long value, const ValueType valueType)
    : ValueToken{TYPE_INTEGER, valueType}, value{value} {}

long long IntegerToken::getValue() const { return value; }

IntegerToken& IntegerToken::operator=(const long long newValue) {
    value = newValue;
    return *this;
}

IntegerToken::operator long long() { return value; }

const IntegerToken IntegerToken::ZERO{0LL};
const IntegerToken IntegerToken::ONE{1LL};
const long long IntegerToken::MAX{std::numeric_limits<long long>::max()};
const long long IntegerToken::MIN{std::numeric_limits<long long>::min()};