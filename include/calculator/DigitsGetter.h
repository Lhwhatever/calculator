#ifndef CALC__DIGITS_GETTER_H_
#define CALC__DIGITS_GETTER_H_

#include <iomanip>
#include <iostream>
#include <sstream>
#include <type_traits>

#include "calculator/NumFormatter.h"

namespace digits {

namespace fixedPt {

/**
 * @brief Get the digits of a floating-point number in fixed-point notation.
 *
 * @tparam Floating The type of the floating-point number.
 * @param num The floating-point number.
 * @param precision Number of decimal places to express the number to.
 * @return std::string The digits.
 */
template <typename Floating>
inline std::string get(Floating num, int precision) {
    std::ostringstream sstream;
    sstream << std::fixed << std::setprecision(precision) << num;
    return sstream.str();
}

/**
 * @brief Get a floating-point number's digits to the maximum precision.
 *
 * @tparam Floating The type of the floating-point number.
 * @param num The floating-point number.
 * @return std::string The digits.
 */
template <typename Floating>
inline std::string getMostPrecisely(Floating num) {
    return get(num, std::numeric_limits<Floating>::digits10);
}

/**
 * @brief Get a floating-point number's digits with auto precision.
 *
 * @tparam Floating The type of the floating-point number.
 * @param num The floating-point number.
 * @param maxConsecDigits Maximum number of consecutive 0s or 9s allowed.
 * @return std::string The digits.
 */
template <typename Floating>
inline std::string getWithAutoPrecision(Floating num, int maxConsecDigits) {
    const std::string rawDigits{getMostPrecisely(num)};
    const int precision{
        formatter::deducePrecision(cbegin(rawDigits) + rawDigits.find('.') + 1,
                                   cend(rawDigits), maxConsecDigits)};
    return digits::fixedPt::get(num, precision);
}

}  // namespace fixedPt

namespace sciNotn {

/**
 * @brief Get the digits of a number in scientific notation.
 *
 * @tparam Number The type of the number.
 * @param num The number.
 * @param precision Number of significant digits in mantissa.
 * @return std::string The digits of the number.
 */
template <typename Number>
inline std::string get(Number num, int precision) {
    std::ostringstream ss;
    ss << std::scientific << std::setprecision(precision) << num;
    return ss.str();
}

/**
 * @brief Get the digits of a number in scientific notation with auto precision.
 *
 * @tparam Number The type of the number.
 * @param num The number.
 * @param maxConsecDigits Maximum consecutive 0s or 9s allowed in the number.
 * @return std::string The digits of the number.
 */
template <typename Number>
inline std::string getWithAutoPrecision(Number num, int maxConsecDigits) {
    if constexpr (std::is_integral_v<Number>)
        return getWithAutoPrecision(static_cast<long double>(num),
                                    maxConsecDigits);
    const auto PRECISION{std::numeric_limits<Number>::digits10};
    const auto rawDigits{get(num, PRECISION)};
    const auto iterBefMantissa{cbegin(rawDigits) + (num < 0 ? 3 : 2)};
    const auto precision{formatter::deducePrecision(
        iterBefMantissa, iterBefMantissa + PRECISION, maxConsecDigits)};
    return get(num, precision);
}

/**
 * @brief Get the exponent from a scientific-notation expression.
 *
 * @tparam InputIt Type of the iterator for the string
 * @param endOfStrIt The iterator pointing to the end of the string
 * @return int The exponent.
 */
template <typename InputIt>
inline int getExponent(InputIt endOfStrIt) {
    int exp{};
    for (int i{1};; i *= 10) {
        auto c{*(--endOfStrIt)};
        if (c == '+') return exp;
        if (c == '-') {
            return -exp;
        }
        exp += (c - '0') * i;
    }
}

}  // namespace sciNotn

namespace engNotn {
constexpr int GROUP{3};

constexpr int calculateShift(int exponent) {
    int remainder{exponent % GROUP};
    return (remainder < 0) ? remainder + GROUP : remainder;
}
}  // namespace engNotn

};  // namespace digits

#endif