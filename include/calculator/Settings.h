#ifndef CALC__SETTINGS_H_
#define CALC__SETTINGS_H_

#include "calculator/SubjectWrapper.h"
#include "calculator/ValueT.h"

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

    bool floatUseAutoPrecision{true}; /**< Use auto-precision for floats. */

    /**
     * @brief Threshold for auto-precision.
     *
     * In auto precision, if at least this number of consecutive zeroes are
     * detected beyond the decimal point, the characters starting from the first
     * zero are ignored. (Exception: the float will always show at least 1
     * decimal place.)
     */
    uint8_t autoPrecisionMaxConsecDigits{4};

    /**
     * @brief Number of decimal places when displaying floats as fixed-point.
     *
     */
    uint8_t floatFixedPtFixedPrecision{4};
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
    CREATE_OPTION(bool, floatUseAutoPrecision)
    CREATE_OPTION(uint8_t, autoPrecisionMaxConsecDigits)
    CREATE_OPTION(uint8_t, floatFixedPtFixedPrecision)

    SettingsImpl make() { return std::move(s); }

   private:
    SettingsImpl s;
};

namespace refactor {

using Settings = SubjectWrapper<SettingsImpl>;

}  // namespace refactor

#endif