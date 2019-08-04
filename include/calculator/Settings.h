#ifndef CALC__SETTINGS_H_
#define CALC__SETTINGS_H_

#include "calculator/SubjectWrapper.h"
#include "calculator/ValueT.h"

namespace modes {

/**
 * @brief Represents possible precision modes in fixed-point notation.
 *
 * `DEC_PT`: to a specified number of decimal places
 * `SIG_FIG`: to a specified number of significant figures
 * `AUTO`: to the maximum precision that prevents a certain number of
 * consecutive 0s or 9s from showing
 */
enum class FixedPtPrecision { DEC_PT, SIG_FIG, AUTO };
};  // namespace modes

/**
 * @brief Represents program settings.
 *
 */
struct SettingsImpl {
    // Formatting Settings

    /**
     * @brief Digits per group before decimal point.
     *
     * Setting to a sufficiently large number (e.g. >40 or simply casting from
     * -1) will cause no grouping to occur. Alternatively, set `sepBefDecimal`
     * to `""`.
     */
    uint8_t grpBefDecimal{3};
    std::string sepBefDecimal{" "}; /**< Separator before decimal point. */

    std::string decimalPt{"."}; /**< Decimal point to use. */

    /**
     * @brief Digits per group after decimal point.
     *
     * Setting to a sufficiently large number (e.g. >40 or simply casting from
     * -1) will cause no grouping to occur. Alternatively, set `sepAftDecimal`
     * to `""`.
     */
    uint8_t grpAftDecimal{3};
    std::string sepAftDecimal{" "}; /**< Separator after decimal point. */

    /**
     * @brief Show leading 0 when expressing a float in fixed-point notation.
     *
     */
    bool floatFixedPtDoLeading0{true};

    /**
     * @brief Precision mode for floating-point numbers in fixed-point mode.
     *
     */
    modes::FixedPtPrecision floatFixedPtPrecisionMode{
        modes::FixedPtPrecision::AUTO};

    /**
     * @brief Threshold for auto-precision.
     *
     * In auto precision, if at least this number of consecutive zeroes are
     * detected beyond the decimal point, the characters starting from the first
     * zero are ignored. (Exception: will always show at least 1 decimal place.)
     */
    uint8_t autoPrecisionMaxConsecDigits{4};

    /**
     * @brief Number of decimal places when displaying floats as fixed-point.
     *
     */
    uint8_t floatFixedPtFixedPrecision{4};

    /**
     * @brief Omit a `+` sign in exponents.
     *
     */
    bool omitPlusInExponent{false};

    /**
     * @brief Exponent to use in scientific notation.
     *
     */
    std::string sciNotnExponent{"e"};

    /**
     * @brief Number of significant digits to display in scientific notation.
     *
     * Set to 0 for auto precision.
     */
    uint8_t sciNotnPrecision{0};

    /**
     * @brief Precision level in engineering notation.
     *
     * Set to 0 for auto precision.
     */
    uint8_t engNotnPrecision{0};
};

/**
 * @brief Used to create a `SettingsImpl` instance using the Builder pattern.
 *
 */
struct SettingsBuilder {
#define CREATE_OPTION(TYPE, NAME)   \
    SettingsBuilder& NAME(TYPE x) { \
        s.NAME = x;                 \
        return *this;               \
    }

    CREATE_OPTION(uint8_t, grpBefDecimal)
    CREATE_OPTION(std::string, sepBefDecimal)
    CREATE_OPTION(std::string, decimalPt)
    CREATE_OPTION(uint8_t, grpAftDecimal)
    CREATE_OPTION(std::string, sepAftDecimal)
    CREATE_OPTION(bool, floatFixedPtDoLeading0)
    CREATE_OPTION(modes::FixedPtPrecision, floatFixedPtPrecisionMode)
    CREATE_OPTION(uint8_t, autoPrecisionMaxConsecDigits)
    CREATE_OPTION(uint8_t, floatFixedPtFixedPrecision)

    CREATE_OPTION(bool, omitPlusInExponent)
    CREATE_OPTION(std::string, sciNotnExponent)
    CREATE_OPTION(uint8_t, sciNotnPrecision);
    CREATE_OPTION(uint8_t, engNotnPrecision);

    SettingsImpl make() { return std::move(s); }

   private:
    SettingsImpl s;
};

namespace refactor {

using Settings = SubjectWrapper<SettingsImpl>;

}  // namespace refactor

#endif