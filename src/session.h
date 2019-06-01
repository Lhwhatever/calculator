#ifndef CALC__SESSION_H_
#define CALC__SESSION_H_

#include <sstream>

#include "io/oStreamHandler.h"
#include "packages/package.h"
#include "settings.h"
#include "tokens/tokenQueue.h"

namespace input_prompt {
const std::string GET_INPUT_TOKEN = "> ";
const std::string INPUT_TOKEN_TABBED = "... ";
}  // namespace input_prompt

class Session {
    enum ParserLoopMode {
        MODE_DEFAULT,
        MODE_INTEGER,
        MODE_FLOAT,
        MODE_FLOAT_EXP,
        MODE_IDENTIFIER,
        MODE_SYMBOL
    };

    using BeginTokenImpl = bool (*)(Session&, ParserLoopMode&, const char&,
                                    std::string::const_iterator&,
                                    std::string::const_iterator&);
    using FlushFunction = void (*)(Session&, ParserLoopMode&);

    Settings settings;
    std::istream& istream;
    OStreamHandler ostream;
    std::ostream& errstream;
    TokenQueue tokenQueue;
    FuncSet funcs;
    std::stringstream tokenBuilder;

    bool allowInfix;

   public:
    Session(const Settings& settings = Settings::DEFAULT,
            std::istream& istream = std::cin, std::ostream& ostream = std::cout,
            std::ostream& errstream = std::cerr);

    ~Session();

   private:
    void emptyTokenBuilder();
    void processCommands(const std::string& expr);

    static bool beginToken__infix(Session& s, ParserLoopMode& loopMode,
                                  const char& c,
                                  std::string::const_iterator& it,
                                  std::string::const_iterator& end);
    static bool beginToken__RPN(Session& s, ParserLoopMode& loopMode,
                                const char& c, std::string::const_iterator& it,
                                std::string::const_iterator& end);

    BeginTokenImpl beginToken;

    void flushIntegers(ParserLoopMode& loopMode);
    void flushFloats(ParserLoopMode& loopMode);
    static void flushSymbols__RPN(Session& s, ParserLoopMode& loopMode);
    static void flushSymbols__infix(Session& s, ParserLoopMode& loopMode);
    FlushFunction flushSymbols;

   public:
    void loadPackage(const std::string& name);

    std::string read();
    void tokenize(const std::string& expr);
    ValueStack evaluateTokens();
    void displayResults(ValueStack&) const;

    void rep();
    void repl();
};

#endif