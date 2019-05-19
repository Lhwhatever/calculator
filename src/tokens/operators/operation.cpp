#include "operation.h"

Operation::Operation(const Func func, const NumTypePattern pat, const int precd)
    : PATTERN{pat}, operate{func}, PRECEDENCE{precd} {}

unsigned int Operation::getArity() const { return PATTERN.size(); }
int Operation::getPrecedence() const { return PRECEDENCE; }
NumTypePattern Operation::getMatchPattern() const { return PATTERN; }