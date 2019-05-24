#ifndef CALC__SESSION_H_
#define CALC__SESSION_H_

#include <iostream>

#include "packages/package.h"
#include "settings.h"

using TokenDeque = std::deque<std::shared_ptr<Token>>;

namespace input_prompt {
const std::string GET_INPUT_TOKEN = "> ";
const std::string INPUT_TOKEN_TABBED = "... ";
}  // namespace input_prompt

class Session {
   private:
    Settings settings;
    std::istream& istream;
    std::ostream& ostream;
    TokenDeque tokenQueue;
    OperatorMap mapOper;

   public:
    Session(Settings = Settings::DEFAULT, std::istream& istream = std::cin,
            std::ostream& ostream = std::cout);

    ~Session();

   public:
    void loadPackage(const std::string& name);

    std::string getInput();
    void parseExpr(const std::string& expr);
    ValueStack runQueue();
    void displayResults(ValueStack&) const;

    void rep();
    void repl();

#ifdef DEBUG
    void printRPNQueue();
#endif
};

#endif