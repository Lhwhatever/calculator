#ifndef CALC__SESSION_H_
#define CALC__SESSION_H_

#include <iostream>
#include <sstream>

#include "io/oStreamHandler.h"
#include "packages/package.h"
#include "settings.h"

using TokenDeque = std::deque<std::shared_ptr<Token>>;

namespace input_prompt {
const std::string GET_INPUT_TOKEN = "> ";
const std::string INPUT_TOKEN_TABBED = "... ";
}  // namespace input_prompt

class Session {
   private:
    enum ParserLoopMode {
        MODE_DEFAULT,
        MODE_INTEGER,
        MODE_FLOAT,
        MODE_FLOAT_EXP,
        MODE_IDENTIFIER,
        MODE_SYMBOL
    };

    Settings settings;
    std::istream& istream;
    OStreamHandler ostream;
    std::ostream& errstream;
    TokenDeque tokenQueue;
    OperatorMap mapOper;
    std::stringstream tokenBuilder;

   public:
    Session(const Settings& settings = Settings::DEFAULT,
            std::istream& istream = std::cin, std::ostream& ostream = std::cout,
            std::ostream& errstream = std::cerr);

    ~Session();

   private:
    void emptyTokenBuilder();
    void flushIntegers(ParserLoopMode& loopMode);
    void flushFloats(ParserLoopMode& loopMode);
    void flushSymbols__RPN(ParserLoopMode& loopMode);
    void flushSymbols__infix(ParserLoopMode& loopMode);

   public:
    void loadPackage(const std::string& name);

    std::string read();
    void tokenize__RPN(const std::string& expr);
    void tokenize__infix(const std::string& expr);
    ValueStack evaluateTokens();
    void displayResults(ValueStack&) const;

    void rep();
    void repl();

#ifdef DEBUG
    void printRPNQueue();
#endif
};

#endif