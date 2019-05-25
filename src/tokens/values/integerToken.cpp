#include "integerToken.h"

const ValueToken::NumType IntegerToken::TYPE_INTEGER{"integer"};

IntegerToken::IntegerToken(const long long value, const ValueType tokenType)
    : ValueToken{tokenType}, value{value} {}

void IntegerToken::outputTo(std::ostream& ostream) const { ostream << value; }

long long IntegerToken::getValue() const { return value; }

void IntegerToken::setValue(const long long newValue) { value = newValue; }

bool IntegerToken::isZero() const { return value == 0LL; }

bool IntegerToken::isUnity() const { return value == 1LL; }

const ValueToken::NumType& IntegerToken::getNumType() const {
    return IntegerToken::TYPE_INTEGER;
}

IntegerToken& IntegerToken::operator=(const int newValue) {
    value = newValue;
    return *this;
}

IntegerToken& IntegerToken::operator=(const long newValue) {
    value = newValue;
    return *this;
}

IntegerToken& IntegerToken::operator=(const long long newValue) {
    value = newValue;
    return *this;
}

IntegerToken::operator long long() { return value; }

std::string IntegerToken::toString() const { return std::to_string(value); }

const IntegerToken IntegerToken::ZERO{0LL};
const IntegerToken IntegerToken::ONE{1LL};