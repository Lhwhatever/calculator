#ifndef CALC__FIXED_PT_STRINGIFIER_H_
#define CALC__FIXED_PT_STRINGIFIER_H_

#include <algorithm>
#include <cmath>
#include <iostream>

#include "calculator/DigitsGetter.h"
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

    template <typename Number>
    std::string getDigitsToSigFigs(Number num, int sigFigs) const {
        const std::string rawDigits{digits::sciNotn::get(num, sigFigs - 1)};
        auto powerOf10{digits::sciNotn::getExponent(cend(rawDigits))};
        auto neg{num < 0};

        std::string befDecimal{neg ? "-" : ""};
        if (powerOf10 < 0) {  // numbers like 0.5, 0.02
            if (floatFixedPtDoLeading0) befDecimal.push_back('0');

            formatter::DecimalPart decPart{grpAftDecimal, sepAftDecimal};
            while (++powerOf10 < 0) decPart.push('0');  // add zeroes
            decPart.push(rawDigits.at(neg ? 1 : 0));    // add first digit
            const auto itStart{cbegin(rawDigits) + (neg ? 2 : 1)};
            decPart.append(itStart + 1, itStart + sigFigs);
            return befDecimal + decimalPt + decPart.get();
        }

        befDecimal.push_back(rawDigits.at(0));  // add first digit

        // start from first digit after decimal point in scientific notation
        // (second digit)
        auto it{cbegin(rawDigits) + (neg ? 3 : 2)};

        // powerOf10 is now the number of digits left before decimalPt

        if (powerOf10 + 1 < sigFigs) {  // numbers like 1.23, 20.04

            while (powerOf10 > 0) {
                if (powerOf10-- % grpBefDecimal == 0)
                    befDecimal += sepBefDecimal;
                befDecimal.push_back(*it++);
            }

            formatter::DecimalPart decPart{grpAftDecimal, sepAftDecimal};
            char digit{};
            for (;;) {
                digit = *it++;
                if (digit == 'e') break;
                decPart.push(digit);
            }

            return befDecimal + decimalPt + decPart.get();
        }

        // numbers like 2000, 1234
        for (;;) {
            auto digit{*it++};
            if (digit == 'e') break;
            if (powerOf10-- % grpBefDecimal == 0) befDecimal += sepBefDecimal;
            befDecimal.push_back(digit);
        }

        while (powerOf10 > 0) {
            if (powerOf10-- % grpBefDecimal == 0) befDecimal += sepBefDecimal;
            befDecimal.push_back('0');
        }

        return befDecimal;
    }

    template <typename Floating>
    std::string formatFloating(Floating num) const {
        if (floatFixedPtPrecisionMode == modes::FixedPtPrecision::SIG_FIG)
            return getDigitsToSigFigs(num, 4);

        const std::string digits{
            (floatFixedPtPrecisionMode == modes::FixedPtPrecision::AUTO)
                ? digits::fixedPt::getWithAutoPrecision(
                      num, autoPrecisionMaxConsecDigits)
                : digits::fixedPt::get(num, floatFixedPtFixedPrecision)};
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
    bool floatFixedPtDoLeading0;

    modes::FixedPtPrecision floatFixedPtPrecisionMode;
    uint8_t autoPrecisionMaxConsecDigits;
    uint8_t floatFixedPtFixedPrecision;

    constexpr static size_t BUFFER_SIZE{256};
};

#endif