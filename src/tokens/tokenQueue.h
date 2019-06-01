#ifndef CALC__TOKENS__TOKEN_QUEUE_H_
#define CALC__TOKENS__TOKEN_QUEUE_H_

#include <memory>
#include <queue>

#include "operators/funcSet.h"
#include "values/valueToken.h"

using TokenSP = std::shared_ptr<Token>;

class TokenQueue : public std::queue<TokenSP> {
   protected:
    using TokenSP = std::shared_ptr<Token>;
    using ValueTokenSP = std::shared_ptr<ValueToken>;

   public:
    virtual ~TokenQueue();

    TokenSP pop();

    void push(ValueTokenSP&&);
    virtual void push(const FuncTokenSP&);
    void push(TokenSP&);
    virtual void flush();

    void clear();
};

#endif
