#ifndef CALC__FIXED_POINT_STRINGIFER_H_
#define CALC__FIXED_POINT_STRINGIFIER_H_

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <type_traits>

#include "calculator/Settings.h"

/**
 * @brief Expresses a number as a string in fixed-point notation.
 *
 */
class FixedPointStringifier {
   public:
    /**
     * @brief Constructs a stringifier with the given settings.
     *
     * @param    settings    Settings to use when formatting.
     */
    FixedPointStringifier(const SettingsImpl& settings);

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

    std::ostringstream getFixedPrecisionSStream(int precision = 0) const;

    template <typename Integral>
    std::string formatIntegral(Integral num) const {
        std::string digits{std::to_string(num)}, output;
        output.reserve(BUFFER_SIZE);

        auto it{cbegin(digits)};
        formatNegSign(it, output);
        formatBefDecimal(it, cend(digits), output);
        return output;
    }

    template <typename Floating>
    std::string getDigitsWithAutoPrecision(Floating num) const {
        auto sstreamRaw{getFixedPrecisionSStream(
            std::numeric_limits<Floating>::digits10 + 1)};
        sstreamRaw << num;
        std::string digitsRaw{sstreamRaw.str()};

        char repeated{'\0'};
        int precision{}, numConsecDigits{};
        for (auto it{cbegin(digitsRaw) + digitsRaw.find('.') + 1},
             end{cend(digitsRaw)};
             it != end; ++it) {
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
                if (++numConsecDigits <= autoPrecisionMaxConsecDigits) continue;
                auto sstream{getFixedPrecisionSStream(std::max(1, precision))};
                sstream << num;
                return sstream.str();
            }

            repeated = '\0';
            precision += numConsecDigits + 1;
        }

        return digitsRaw;
    }

    template <typename Floating>
    std::string formatFloating(Floating num) const {
        std::string digits{getDigitsWithAutoPrecision(num)}, output;
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
    uint8_t grpAftDecimal;
    std::string sepAftDecimal;
    std::string decimalPt;

    SettingsImpl::Precision floatPrecisionMode;
    uint8_t autoPrecisionMaxConsecDigits;

    constexpr static size_t BUFFER_SIZE{256};
};

#endif