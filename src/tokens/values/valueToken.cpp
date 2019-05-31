#include "valueToken.h"

namespace {
using NumType = ValueToken::NumType;
}

NumType::NumType(std::string description)
    : ID{nextId++}, DESCRIPT{description} {}

std::string NumType::getDescription() const { return DESCRIPT; }
unsigned short NumType::getId() const { return ID; }
void NumType::outputTo(std::ostream& ostream) const { ostream << DESCRIPT; }
NumType::operator std::string() const { return DESCRIPT; }
bool operator==(const NumType& a, const NumType& b) { return a.ID == b.ID; }

unsigned short NumType::nextId{0};
const NumType NumType::TYPE_UNDEFINED{"undefined"};

ValueToken::ValueToken(ValueType valueType) : VALUE_TYPE{valueType} {}
ValueToken::~ValueToken() {}