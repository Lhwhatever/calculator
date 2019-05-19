#ifndef SETTINGS_H_
#define SETTINGS_H_

#include <deque>
#include <iostream>

struct Settings {
    enum ExprParsingMode {
        RPN  // reverse Polish notation
    };

    static const Settings DEFAULT;

    const ExprParsingMode exprParsingMode;

    Settings(const ExprParsingMode mode = RPN);
};

#endif