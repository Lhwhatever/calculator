#ifndef CALC__PRECEDENCE_H_
#define CALC__PRECEDENCE_H_

#include <iostream>

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
     * @param   nominalLevel    The nominal precedence level.
     * @return  `Precedence` instance with left-to-right associativity.
     */
    static Precedence l2r(int nominalLevel);

    /**
     * @brief Creates a `Precedence` instance with right-to-left associativity.
     *
     * @param   nominalLevel    The nominal precedence level.
     * @return  `Precedence` instance with right-to-left associativity.
     */
    static Precedence r2l(int nominalLevel);

    /**
     * @brief Checks if this is left-to-right associative.
     *
     * @return `true` if left-to-right associative; `false` if otherwise.
     */
    bool isL2R() const noexcept;

    /**
     * @brief Checks if this is right-to-left associative.
     *
     * @return `true` if right-to-left associative; `false` if otherwise.
     */
    bool isR2L() const noexcept;

   private:
    int precd;
    enum class Associativity { L2R = 0, R2L = -1 };
    Associativity assoc;

    Precedence(int, Associativity);

    friend std::ostream& operator<<(std::ostream&, Precedence);

    friend bool operator==(Precedence, Precedence);
    friend bool operator!=(Precedence, Precedence);

    friend bool operator>(Precedence, Precedence);
    friend bool operator<(Precedence, Precedence);
    friend bool operator>=(Precedence, Precedence);
    friend bool operator<=(Precedence, Precedence);
};

std::ostream& operator<<(std::ostream&, Precedence);

bool operator==(Precedence, Precedence);
bool operator!=(Precedence, Precedence);

bool operator>(Precedence, Precedence);
bool operator<(Precedence, Precedence);
bool operator>=(Precedence, Precedence);
bool operator<=(Precedence, Precedence);

}  // namespace refactor

#endif