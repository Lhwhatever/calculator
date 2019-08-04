#ifndef CALC__ENG_NOTN_STRINGIFIER_H_
#define CALC__ENG_NOTN_STRINGIFIER_H_

#include "calculator/DigitsGetter.h"
#include "calculator/NumFormatter.h"
#include "calculator/Settings.h"

/**
 * @brief Expresses a number as a string in engineering notation.
 *
 */
class EngNotnStringifier {
   public:
    /**
     * @brief Construct a new `EngNotnStringifier` object with given settings.
     *
     * @param settings Options to use when formatting.
     */
    EngNotnStringifier(const SettingsImpl& settings);

    /**
     * @brief Updates the stringifier with the given settings.
     *
     * @param settings Settings to use when formatting.
     */
    void update(const SettingsImpl& settings);

    /**
     * @brief Formats a number as a string in engineering notation.
     *
     * @tparam Number Type of the numeric value used.
     * @param number The number.
     * @return The numeric value as a string.
     */
    template <class Number>
    std::string operator()(Number num) const {
        const std::string digitsOfNum{digits::sciNotn::getWithAutoPrecision(
            num, autoPrecisionMaxConsecDigits)};

        const int trueExp{digits::sciNotn::getExponent(cend(digitsOfNum))},
            shift{digits::engNotn::calculateShift(trueExp)},
            dispExp{trueExp - shift};

        std::string output;
        formatSignificand(cbegin(digitsOfNum), shift, output);
        output += sciNotnExponent;
        if (dispExp > 0) output.push_back('+');
        output += std::to_string(trueExp - shift);
        return output;
    };

   private:
    using StrConstIt = std::string::const_iterator;

    uint8_t grpAftDecimal;
    std::string sepAftDecimal;
    std::string decimalPt;

    uint8_t autoPrecisionMaxConsecDigits;
    std::string sciNotnExponent;

    void formatSignificand(StrConstIt srcBegin, int shift,
                           std::string& output) const;
};

#endif