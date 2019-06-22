#ifndef CALC__PRECEDENCE_H_
#define CALC__PRECEDENCE_H_

#include <iostream>
#include <limits>

namespace refactor {

/**
 * @brief Represents the precedence of an operator.
 *
 * This encompasses the two properties concerned when parsing operators: its
 * precedence and associativity.
 *
 * Technically, all operators of the same precedence level should have the same
 * associativity (e.g. + and - have the same precedence level and are both
 * left-associative.)
 *
 * However, due to the unnecessary overhead it would incur to enforce this, we
 * treat left-associative operators as being 'half a level' higher than
 * right-associative operators of the same nominal precedence level.
 */
struct Precedence {
    /**
     * @brief Creates a `Precedence` instance with left-to-right
     * associativity.
     *
     * @param   nominalLvl  The nominal precedence level.
     * @return  `Precedence` instance with left-to-right associativity.
     */
    constexpr static Precedence l2r(short nominalLvl) noexcept {
        return {
            static_cast<unsigned int>(nominalLvl + offsetValueForNominalLvl0)
                << 1u |
            maskL2RAssoc};
    }

    /**
     * @brief Creates a `Precedence` instance with right-to-left associativity.
     *
     * @param   nominalLvl  The nominal precedence level.
     * @return  `Precedence` instance with right-to-left associativity.
     */
    constexpr static Precedence r2l(short nominalLvl) noexcept {
        return {
            static_cast<unsigned int>(nominalLvl + offsetValueForNominalLvl0)
            << 1u};
    }

    /**
     * @brief Checks if this is left-to-right associative.
     *
     * @return `true` if left-to-right associative; `false` if otherwise.
     */
    constexpr bool isL2R() const noexcept { return val & maskL2RAssoc; };

    /**
     * @brief Checks if this is right-to-left associative.
     *
     * @return `true` if right-to-left associative; `false` if otherwise.
     */
    constexpr bool isR2L() const noexcept { return !(val & maskL2RAssoc); };

   private:
    constexpr static int offsetValueForNominalLvl0 =
        -std::numeric_limits<short>::min();

    constexpr static unsigned int maskL2RAssoc = 1u;

    unsigned int val;

    constexpr Precedence(unsigned int x) : val{x} {}

    friend std::ostream& operator<<(std::ostream&, Precedence);

    friend constexpr bool operator==(Precedence, Precedence);
    friend constexpr bool operator!=(Precedence, Precedence);
    friend constexpr bool operator>(Precedence, Precedence);
    friend constexpr bool operator<(Precedence, Precedence);
    friend constexpr bool operator>=(Precedence, Precedence);
    friend constexpr bool operator<=(Precedence, Precedence);
};

std::ostream& operator<<(std::ostream&, Precedence);

constexpr bool operator==(Precedence a, Precedence b) { return a.val == b.val; }
constexpr bool operator!=(Precedence a, Precedence b) { return a.val != b.val; }
constexpr bool operator>(Precedence a, Precedence b) { return a.val > b.val; }
constexpr bool operator<(Precedence a, Precedence b) { return a.val < b.val; }
constexpr bool operator>=(Precedence a, Precedence b) { return a.val >= b.val; }
constexpr bool operator<=(Precedence a, Precedence b) { return a.val <= b.val; }

}  // namespace refactor

#endif