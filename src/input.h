#ifndef INPUT_H_
#define INPUT_H_

#include <iostream>
#include <string>

#include "settings.h"
#include "tokens/operators/operatorToken.h"

namespace input_prompt {
const std::string GET_INPUT_TOKEN = "> ";
const std::string INPUT_TOKEN_TABBED = "... ";
}  // namespace input_prompt

class Environment {
   public:
    settings::ExprParsingMode exprParsingMode;
    std::istream& istream;
    std::ostream& ostream;
    std::deque<Token*> tokenQueueRPN;

   public:
    Environment(settings::ExprParsingMode exprParsingMode = settings::RPN,
                std::istream& istream = std::cin,
                std::ostream& ostream = std::cout);

    ~Environment();

   public:
    std::string getInput();
    void parseExpr(const std::string& expr);
    void runRPNQueue();

    void tick();

    void printRPNQueue();
};

#endif