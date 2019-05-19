#include "valueToken.h"

using NumericType = ValueToken::NumericType;

const NumericType NumericType::TYPE_UNDEFINED{"undefined"};

std::string NumericType::getDescription() const { return DESCRIPT; }
void NumericType::outputTo(std::ostream& ostream) const { ostream << DESCRIPT; }
NumericType::operator std::string() const { return DESCRIPT; }

ValueToken::ValueToken(ValueType valueType) : VALUE_TYPE{valueType} {}
const NumericType const& ValueToken::getNumericType() const {
    return NumericType::TYPE_UNDEFINED;
}