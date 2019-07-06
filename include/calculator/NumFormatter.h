#ifndef CALC__NUM_FORMATTER_H_
#define CALC__NUM_FORMATTER_H_

#include <string>

namespace formatter {

template <typename InputIt>
inline int deducePrecision(const InputIt rawDigitsIterAftDecimal,
                           const InputIt rawDigitsEnd,
                           const uint8_t maxConsecDigits) {
    char repeated{'\0'};
    int precision{}, numConsecDigits{};
    for (auto it{rawDigitsIterAftDecimal}; it != rawDigitsEnd; ++it) {
        auto ch{*it};
        if (repeated == '\0') {
            if (ch == '0' || ch == '9') {
                repeated = ch;
                numConsecDigits = 1;
                continue;
            }
            ++precision;
            continue;
        }

        if (ch == repeated) {
            if (++numConsecDigits <= maxConsecDigits) continue;
            break;
        }

        repeated = '\0';
        precision += numConsecDigits + 1;
    }
    return std::max(1, precision);
}
};  // namespace formatter

#endif