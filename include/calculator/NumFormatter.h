#ifndef CALC__NUM_FORMATTER_H_
#define CALC__NUM_FORMATTER_H_

#include <string>

namespace formatter {

/**
 * @brief Represents fractional part of a decimal expansion.
 *
 */
class DecimalPart {
    const int group;
    const std::string sep;
    std::string s;
    int sinceLastSep{};

   public:
    DecimalPart(int group, const std::string& separator);

    /**
     * @brief Adds a digit to the fractional part.
     *
     * @param digit Digit to add.
     */
    void push(char digit);

    /**
     * @brief Appends a sequence of digits using an iterator pattern.
     *
     * @tparam InputIt Type of the iterator
     * @param itBegin Iterator pointing to the start of the sequence.
     * @param itEnd Iterator pointing to the end of the sequence.
     */
    template <typename InputIt>
    void append(const InputIt itBegin, const InputIt itEnd) {
        for (auto it{itBegin}; it != itEnd; ++it) push(*it);
    }

    /**
     * @brief Gets the formatted sequence of digits.
     *
     * @return std::string The formatted sequence of digits.
     */
    std::string get();

    /**
     * @brief Resets the internal state.
     *
     */
    void reset();
};

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