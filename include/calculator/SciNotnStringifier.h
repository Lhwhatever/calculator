#ifndef CALC__SCI_NOTN_STRINGIFIER_H_
#define CALC__SCI_NOTN_STRINGIFIER_H_

#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>

#include "calculator/DigitsGetter.h"
#include "calculator/NumFormatter.h"
#include "calculator/Settings.h"

/**
 * @brief Expresses a number as a string in scientific notation.
 *
 */
class SciNotnStringifier {
   public:
    /**
     * @brief Construct a new `SciNotnStringifier` object with given options.
     *
     * @param   settings    Options to use when formatting.
     */
    SciNotnStringifier(const SettingsImpl& settings);

    /**
     * @brief Updates the stringifier with the given settings.
     *
     * @param   settings    Settings to use when formatting.
     */
    void update(const SettingsImpl& settings);

    /**
     * @brief Formats a numeric value as a string in scientific notation.
     *
     * @tparam  Number      Type of the numeric value
     * @param   num         The numeric value to format.
     * @return  The numeric value as a string in scientific notation.
     */
    template <typename Number>
    std::string operator()(Number num) const {
        const std::string rawDigits{
            sciNotnPrecision ? digits::sciNotn::get(num, sciNotnPrecision - 1)
                             : digits::sciNotn::getWithAutoPrecision(
                                   num, autoPrecisionMaxConsecDigits)};
        std::string output;
        output.reserve(BUFFER_SIZE);

        auto digitsIt{cbegin(rawDigits)};
        digitsIt = formatSignificand(digitsIt, output);
        formatExponent(digitsIt, cend(rawDigits), output);
        return output;
    }

   private:
    using StrConstIt = std::string::const_iterator;

    StrConstIt formatSignificand(StrConstIt srcBegin,
                                 std::string& output) const;
    void formatExponent(StrConstIt srcItAtExp, StrConstIt srcEnd,
                        std::string& output) const;

    uint8_t grpAftDecimal;
    std::string sepAftDecimal;
    std::string decimalPt;
    uint8_t autoPrecisionMaxConsecDigits;
    bool omitPlusInExponent;
    std::string sciNotnExponent;
    uint8_t sciNotnPrecision;

    const static size_t BUFFER_SIZE{256};
};

#endif