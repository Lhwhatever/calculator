#ifndef CALC__TOKENIZER__TOKENIZER_H_
#define CALC__TOKENIZER__TOKENIZER_H_

#include <sstream>

#include "../settings.h"
#include "../tokens/tokenQueue.h"

class Tokenizer {
    enum LoopMode {
        MODE_DEFAULT,
        MODE_INTEGER,
        MODE_FLOAT,
        MODE_FLOAT_EXP,
        MODE_IDENTIFIER,
        MODE_SYMBOL
    };

    using FuncFlushSym = void (Tokenizer::*)(const FuncSet&, TokenQueue&);

    template <typename T>
    using Supplier = T (Tokenizer::*)();

    std::stringstream tokenBuilder;
    std::string::const_iterator it;
    std::string::const_iterator end;

    bool allowInfixNext;
    LoopMode loopMode;
    const Settings& settings;

   public:
    Tokenizer(const Settings& s);

   private:
    bool beginToken__RPN();
    bool beginToken__infix();
    Supplier<bool> beginToken;
    void flushSymbols__RPN(const FuncSet&, TokenQueue&);
    void flushSymbols__infix(const FuncSet&, TokenQueue&);

    void emptyTokenBuilder();
    void flushIntegers(TokenQueue&);
    void flushFloats(TokenQueue&);
    FuncFlushSym flushSymbols;
    void flushAll(const FuncSet&, TokenQueue&);

    void tick(const FuncSet& funcs, TokenQueue& output);

   public:
    void tokenize(const std::string& input, const FuncSet& funcs,
                  TokenQueue& output);
};

#endif