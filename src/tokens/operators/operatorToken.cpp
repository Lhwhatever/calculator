#include "operatorToken.h"

#include <functional>

#include "../../except/arityMismatchException.h"
#include "../../except/noOperationException.h"

OperatorToken::OperatorToken(const std::string id, const unsigned int arity,
                             const int precd,
                             const OperatorToken::Associativity assoc)
    : ID{id}, ARITY{arity}, PRECD{precd}, ASSOC{assoc}, operations{} {}

OperatorToken::OperatorToken(const OperatorToken& tok, const std::string& alias,
                             const int precd)
    : ID{alias},
      ARITY{tok.ARITY},
      PRECD{precd},
      ASSOC{tok.ASSOC},
      operations{tok.operations} {
    if (alias == tok.ID) throw "illegal replication";
}

OperatorToken::OperatorToken(const OperatorToken& tok, const std::string& alias)
    : OperatorToken{tok, alias, tok.PRECD} {}

void OperatorToken::outputTo(std::ostream& ostream) const {
    ostream << toString();
}

std::string OperatorToken::toString() const { return getIdentifier(); }
const std::string& OperatorToken::getIdentifier() const { return ID; }
void OperatorToken::setIdentifier(const std::string& id) { ID = id; }

unsigned int OperatorToken::getArity() const { return ARITY; }
int OperatorToken::getPrecedence() const { return PRECD; }
OperatorToken::Associativity OperatorToken::getAssociativity() const {
    return ASSOC;
}

void OperatorToken::bind(const NumTypePattern& pattern, const Operation& oper) {
    if (pattern.size() != ARITY)
        throw ArityMismatchException(
            ID, ARITY, pattern.size(),
            "when binding new Operation to OperatorToken");

    operations.try_emplace(pattern, oper);
}

void OperatorToken::operate(ValueStack& values) {
    auto size{values.size()};
    if (size < ARITY)
        throw ArityMismatchException(ID, ARITY, size,
                                     "when executing operation");

    NumTypePattern pattern(ARITY);
    for (int i = size - ARITY, s = size; i < s; ++i)
        pattern.push_back(values[i]->getNumType());

    if (operations.find(pattern) == operations.end())
        throw NoOperationException("no operation could be found");

    operations.at(pattern)(values);
}