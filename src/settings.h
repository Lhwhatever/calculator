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
    const char digitSep;
    const unsigned int digitSepInterval;
    const char decimalSign;

    Settings(const ExprSyntax exprSyntax = SYNTAX_RPN,
             const char digitSep = '_', const unsigned int digitSepInterval = 3,
             const char decimalSign = '.');
};

#endif