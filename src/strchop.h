#ifndef STRCHOP_H
#define STRCHOP_H

#include <set>


namespace CHARS {
    extern std::set<char> SYMBOLS;
}


inline bool isNumeric(char c) {
    return c >= '0' && c <= '9';
}

inline bool isAlphabetical(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

inline bool isAlphanumeric(char c) {
    return isAlphabetical(c) || isNumeric(c);
}

inline bool isWhitespace(char c) {
    return c == ' ';
}

inline bool isSymbolic(char c) {
    return CHARS::SYMBOLS.find(c) != CHARS::SYMBOLS.end();
}


#endif