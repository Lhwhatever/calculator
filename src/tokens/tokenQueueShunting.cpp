#include "tokenQueueShunting.h"

bool ShuntingTokenQueue::shouldPopFStack(const FuncTokenSP& newFunc) {
    auto& topFunc{fstack.top()};
    return (topFunc->PREC > newFunc->PREC) ||
           (topFunc->PREC == newFunc->PREC &&
            newFunc->PREC.assoc == Precedence::ASSOC_L2R);
}

void ShuntingTokenQueue::takeFromFStack() {
    push(fstack.top());
    fstack.pop();
}

void ShuntingTokenQueue::push(const FuncTokenSP& func) {
    if (func->ARITY == 1)
        while (shouldPopFStack(func) && fstack.top()->ARITY == 1)
            takeFromFStack();
    else
        while (shouldPopFStack(func)) takeFromFStack();
}

void ShuntingTokenQueue::flush() {
    while (!fstack.empty()) takeFromFStack();
}