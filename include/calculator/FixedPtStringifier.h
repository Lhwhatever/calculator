#ifndef CALC__FIXED_PT_STRINGIFIER_H_
#define CALC__FIXED_PT_STRINGIFIER_H_

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <type_traits>

#include "calculator/NumFormatter.h"
#include "calculator/Settings.h"

/**
 * @brief Expresses a number as a string in fixed-point notation.
 *
 */
class FixedPtStringifier {
   public:
    /**
     * @brief Constructs a stringifier with the given settings.
     *
     * @param    settings    Settings to use when formatting.
     */
    FixedPtStringifier(const SettingsImpl& settings);

    /**
     * @brief Updates the stringifier with the given settings.
     *
     * @param   settings    Settings to use when formatting.
     */
    void update(const SettingsImpl& settings);

    /**
     * @brief Formats a numeric value as a string in fixed-point notation.
     *
     * @tparam  Number      Type of the numeric value
     * @param   num         The numeric value to format.
     * @return  The numeric value as a string in fixed-point notation.
     */
    template <typename Number>
    std::string operator()(Number num) const {
        if constexpr (std::is_integral_v<Number>) return formatIntegral(num);
        if constexpr (std::is_floating_point_v<Number>)
            return formatFloating(num);
        static_assert("Numeric type expected.");
    }

   private:
    std::string generateOutputBuffer() const;

    void formatNegSign(std::string::const_iterator& srcBegin,
                       std::string& output) const;

    void formatBefDecimal(std::string::const_iterator srcBegin,
                          std::string::const_iterator srcEnd,
                          std::string& output) const;

    void formatAftDecimal(std::string::const_iterator srcItAtDecimal,
                          std::string::const_iterator srcEnd,
                          std::string& output) const;

    static std::ostringstream getFixedPrecisionSStream(int precision = 0);

    template <typename Integral>
    std::string formatIntegral(Integral num) const {
        std::string output;
        const std::string digits{std::to_string(num)};
        output.reserve(BUFFER_SIZE);

        auto it{cbegin(digits)};
        formatNegSign(it, output);
        formatBefDecimal(it, cend(digits), output);
        return output;
    }

    template <typename Floating>
    static std::string getDigitsWithPrecision(Floating num, int precision) {
        auto sstream{getFixedPrecisionSStream(precision)};
        sstream << num;
        return sstream.str();
    }

    template <typename Floating>
    static std::string getDigitsWithMaxPrecision(Floating num) {
        return getDigitsWithPrecision(
            num, std::numeric_limits<Floating>::digits10 + 1);
    }

    template <typename Floating>
    std::string getDigitsWithAutoPrecision(Floating num) const {
        const std::string rawDigits{getDigitsWithMaxPrecision(num)};
        const int precision{formatter::deducePrecision(
            cbegin(rawDigits) + rawDigits.find('.') + 1, cend(rawDigits),
            autoPrecisionMaxConsecDigits)};
        return getDigitsWithPrecision(num, precision);
    }

    template <typename Floating>
    std::string formatFloating(Floating num) const {
        const std::string digits{
            floatUseAutoPrecision
                ? getDigitsWithAutoPrecision(num)
                : getDigitsWithPrecision(num, floatFixedPtFixedPrecision)};
        std::string output;
        output.reserve(BUFFER_SIZE);

        auto it{cbegin(digits)}, decimal{it + digits.find('.')};
        formatNegSign(it, output);
        formatBefDecimal(it, decimal, output);
        output += decimalPt;
        formatAftDecimal(decimal, cend(digits), output);
        return output;
    };

    uint8_t grpBefDecimal;
    std::string sepBefDecimal;
    std::string decimalPt;
    uint8_t grpAftDecimal;
    std::string sepAftDecimal;

    bool floatUseAutoPrecision;
    uint8_t autoPrecisionMaxConsecDigits;
    uint8_t floatFixedPtFixedPrecision;

    constexpr static size_t BUFFER_SIZE{256};
};

#endif