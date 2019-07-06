#ifndef CALC__SCI_NOTN_STRINGIFIER_H_
#define CALC__SCI_NOTN_STRINGIFIER_H_

#include <iomanip>
#include <limits>
#include <sstream>

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
        const std::string digits{getDigitsWithAutoPrecision(num)};
        std::string output;
        output.reserve(BUFFER_SIZE);

        auto digitsIt{cbegin(digits)};
        digitsIt = formatPreMantissa(digitsIt, output);
        digitsIt = formatMantissa(digitsIt, output);
        formatExponent(digitsIt, cend(digits), output);
        return output;
    }

   private:
    template <typename Number>
    static std::string getDigitsWithPrecision(Number num, int precision) {
        std::ostringstream ss;
        ss << std::scientific << std::setprecision(precision) << num;
        return ss.str();
    }

    template <typename Number>
    std::string getDigitsWithAutoPrecision(Number num) const {
        if constexpr (std::is_integral_v<Number>)
            return getDigitsWithAutoPrecision(static_cast<long double>(num));
        const auto rawDigits{getDigitsWithPrecision(num, PRECISION)};
        const auto iterBefMantissa{cbegin(rawDigits) + (num < 0 ? 3 : 2)};
        const auto precision{formatter::deducePrecision(
            iterBefMantissa, iterBefMantissa + PRECISION,
            autoPrecisionMaxConsecDigits)};
        return getDigitsWithPrecision(num, precision);
    }

    using StrConstIt = std::string::const_iterator;

    StrConstIt formatPreMantissa(StrConstIt srcBegin,
                                 std::string& output) const;
    StrConstIt formatMantissa(StrConstIt srcMantissaBegin,
                              std::string& output) const;
    void formatExponent(StrConstIt srcItAtExp, StrConstIt srcEnd,
                        std::string& output) const;

    uint8_t grpAftDecimal;
    std::string sepAftDecimal;
    std::string decimalPt;
    uint8_t autoPrecisionMaxConsecDigits;
    std::string sciNotnExponent;

    const static size_t BUFFER_SIZE{256};
    constexpr static int PRECISION{std::numeric_limits<long double>::digits10};
};

#endif