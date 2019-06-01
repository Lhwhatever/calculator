#ifndef CALC__TOKENS__TOKEN_QUEUE_SHUNTING_H_
#define CALC__TOKENS__TOKEN_QUEUE_SHUNTING_H_

#include <stack>

#include "tokenQueue.h"

class ShuntingTokenQueue : public TokenQueue {
    using FStack = std::stack<FuncTokenSP>;

    FStack fstack;
    bool shouldPopFStack(FuncTokenSP& newFunc);
    void takeFromFStack();

   public:
    virtual void push(FuncTokenSP&) override;
    virtual void flush() override;
};

#endif