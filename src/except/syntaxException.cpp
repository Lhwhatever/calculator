#include "syntaxException.h"

#include <sstream>

SyntaxException::SyntaxException(std::string str) : STR{str} {}

const char* SyntaxException::what() const noexcept {
    return ("syntax error: unexpected character " + STR).c_str();
}