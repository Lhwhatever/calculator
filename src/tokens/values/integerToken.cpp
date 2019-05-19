#include "integerToken.h"

const ValueToken::NumericType IntegerToken::TYPE_INTEGER{"integer"};

IntegerToken::IntegerToken(const long value, const ValueType tokenType)
    : ValueToken{tokenType}, value{value} {}

void IntegerToken::outputTo(std::ostream& ostream) const { ostream << value; }

long IntegerToken::getValue() const { return value; }

void IntegerToken::setValue(long newValue) { value = newValue; }

bool IntegerToken::isZero() const { return value == 0; }

bool IntegerToken::isUnity() const { return value == 1; }

const ValueToken::NumericType& IntegerToken::getNumericType() const {
    return IntegerToken::TYPE_INTEGER;
}

IntegerToken& IntegerToken::operator=(const long newValue) { value = newValue; }

IntegerToken::operator long() { return value; }

std::string IntegerToken::toString() const { return std::to_string(value); }

IntegerToken IntegerToken::ZERO{0};
IntegerToken IntegerToken::ONE{1};