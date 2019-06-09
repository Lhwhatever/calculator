#ifndef CALC__VALUE_TOKEN_H_
#define CALC__VALUE_TOKEN_H_

#include "AbstractToken.h"
#include "ValueTypes.h"

/** @ingroup tokens
 * @brief A token that contains a value.
 *
 * Superclass of all tokens representing value.
 */
class AbstractValueToken : public AbstractToken {};

namespace refactor {
/** @ingroup tokens
 * @brief Concrete class of a value-containing token.
 *
 * Note that in ths implementation, the value stored is immutable.
 * @tparam T    type of value stored
 */
template <class T>
class ValueToken : public AbstractValueToken {
    static_assert(ValueTypes<T>::ALLOWED && "This type is not allowed");

    const T value;

   public:
    typedef T type; /**< Type of value stored. */

   public:
    /**
     * @brief Constructs with the specified value stored.
     *
     * @param[in]   value   Value to store.
     */
    ValueToken(const T& value) : value{value} {};

    /**
     * @brief Gets the stored value.
     *
     * @return Stored value.
     */
    const T& getValue() const { return value; };

    /**
     * @brief Implements the Visitor pattern on `ValueToken`.
     *
     * Uses the implementation offered by `AbstractTokenHandler`.
     */
    virtual void accept(AbstractTokenHandler&) const override{};
};

/** @ingroup tokens
 * @brief Token containing an integer value.
 *
 * Implementation of `AbstractValueToken` for integer types. Underlying type
 * used is `long long`.
 */
using IntegerToken = ValueToken<long long>;

/** @ingroup tokens
 * @brief Token containing a floating-point value.
 *
 * Implementation of `AbstractValueToken` for floating-point types. Underlying
 * type used is `long double`.
 */
using FloatPtToken = ValueToken<long double>;

}  // namespace refactor

#endif