#include "tokenQueue.h"

TokenQueue::~TokenQueue() {}

TokenSP TokenQueue::pop() {
    auto f{front()};
    std::queue<TokenSP>::pop();
    return f;
}

void TokenQueue::push(ValueTokenSP&& val) { std::queue<TokenSP>::push(val); }
void TokenQueue::push(const FuncTokenSP& ft) { std::queue<TokenSP>::push(ft); }
void TokenQueue::push(TokenSP& op) { std::queue<TokenSP>::push(op); }
void TokenQueue::flush() {}

void TokenQueue::clear() { c.clear(); }