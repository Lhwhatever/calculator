#include "valueToken.h"

#include <functional>

namespace {
using NumType = ValueToken::NumType;
}

std::vector<ValueToken::NumTypeR> NumType::types;

NumType::NumType(const std::string& name)
    : ID{static_cast<unsigned short>(types.size())}, NAME{name} {
    types.push_back(std::cref(*this));
}

const NumType& NumType::getById(const unsigned short id) {
    return types.at(id);
}

const NumType NumType::TYPE_UNDEFINED{"undefined"};

bool operator==(const NumType& a, const NumType& b) { return a.ID == b.ID; }

ValueToken::ValueToken(const NumType& numType, const ValueType valueType)
    : Token{Token::CAT_VALUE}, TYPE_VALUE{valueType}, TYPE_NUM{numType} {}

ValueToken::operator ValueToken::ValueType() const { return TYPE_VALUE; }