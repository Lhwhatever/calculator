#include "valueToken.h"

namespace {
using NumType = ValueToken::NumType;
}

std::string NumType::getDescription() const { return DESCRIPT; }
void NumType::outputTo(std::ostream& ostream) const { ostream << DESCRIPT; }
NumType::operator std::string() const { return DESCRIPT; }

ValueToken::ValueToken(ValueType valueType) : VALUE_TYPE{valueType} {}
ValueToken::~ValueToken() {}