#ifndef CALC__SESSION_H_
#define CALC__SESSION_H_

#include "errors/errorWrapped.h"
#include "io/oStreamHandler.h"
#include "packages/package.h"
#include "tokenizer/tokenizer.h"

namespace input_prompt {
const std::string GET_INPUT_TOKEN = "> ";
const std::string INPUT_TOKEN_TABBED = "... ";
}  // namespace input_prompt

class Session {
    Settings settings;
    std::istream& istream;
    OStreamHandler ostream;
    std::ostream& errstream;
    TokenQueue tokenQueue;
    FuncSet funcs;
    ErrorCode errCode;
    Tokenizer tokenizer;

   public:
    Session(const Settings& settings = Settings::DEFAULT,
            std::istream& istream = std::cin, std::ostream& ostream = std::cout,
            std::ostream& errstream = std::cerr);

    ~Session();

   private:
    void processCommands(const std::string& expr);

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