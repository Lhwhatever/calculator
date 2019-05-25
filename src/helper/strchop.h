#ifndef CALC__HELPER__STRCHOP_H_
#define CALC__HELPER__STRCHOP_H_

#include <set>

namespace chars {
extern std::set<char> SYMBOLS;

namespace {
auto symbolend{SYMBOLS.end()};
}

}  // namespace chars

namespace strchop {
inline bool isNumeric(char c) { return c >= '0' && c <= '9'; }

inline bool isAlphabetical(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

inline bool isAlphanumeric(char c) { return isAlphabetical(c) || isNumeric(c); }

inline bool isWhitespace(char c) { return c == ' '; }

inline bool isSymbolic(char c) {
    return chars::SYMBOLS.find(c) != chars::symbolend;
}

inline bool isPrintable(char c) { return c >= ' ' || c != 0x7f; }
}  // namespace strchop

#endif