#include "valueToken.h"

namespace {
using NumType = ValueToken::NumType;
}

NumType::NumType(std::string description)
    : ID{nextId++}, DESCRIPT{description} {}

std::string NumType::getDescription() const { return DESCRIPT; }
unsigned long NumType::getId() const { return ID; }
void NumType::outputTo(std::ostream& ostream) const { ostream << DESCRIPT; }
NumType::operator std::string() const { return DESCRIPT; }
byte NumType::nextId{1};

ValueToken::ValueToken(ValueType valueType) : VALUE_TYPE{valueType} {}
ValueToken::~ValueToken() {}