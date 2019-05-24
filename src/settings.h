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

    Settings(const ExprSyntax exprSyntax = SYNTAX_RPN);
};

#endif