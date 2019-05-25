#ifndef SETTINGS_H_
#define SETTINGS_H_

#include <deque>
#include <iostream>

struct Settings {
    enum ExprSyntax {
        SYNTAX_RPN  // reverse Polish notation
    };

    static const Settings DEFAULT;

    const ExprSyntax exprSyntax;
    const std::string digitSep;
    const unsigned int digitSepInterval;

    Settings(const ExprSyntax exprSyntax = SYNTAX_RPN,
             const std::string digitSep = "_",
             const unsigned int digitSepInterval = 3);
};

#endif