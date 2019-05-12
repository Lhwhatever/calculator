#ifndef SETTINGS_H
#define SETTINGS_H

#include <iostream>
#include <deque>


namespace Settings {
    enum ExprParsingMode {
        RPN // reverse Polish notation
    };
}


class Environment {

public:
    Settings::ExprParsingMode exprParsingMode;
    std::istream& istream;
    std::ostream& ostream;
    std::deque<Token*> tokenQueueRPN;

public:
    Environment(Settings::ExprParsingMode exprParsingMode=Settings::RPN,
        std::istream& istream=std::cin, std::ostream& ostream=std::cout);

    ~Environment();

public:
    void parseExpr(std::string& expr);
    void tick();

    void printRPNQueue();
};


#endif