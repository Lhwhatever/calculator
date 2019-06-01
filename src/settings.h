#ifndef SETTINGS_H_
#define SETTINGS_H_

#include <deque>
#include <iostream>

struct Settings {
    enum ExprSyntax {
        SYNTAX_RPN,
        SYNTAX_INFIX  // reverse Polish notation
    };

    static const Settings DEFAULT;

    const ExprSyntax exprSyntax;
    const char digitSep;
    const int digitSepInterval;
    const char decimalSign;

    Settings(ExprSyntax exprSyntax = SYNTAX_INFIX, char digitSep = '_',
             int digitSepInterval = 3, char decimalSign = '.');
};

#endif