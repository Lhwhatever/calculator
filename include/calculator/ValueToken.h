#ifndef CALC__VALUE_TOKEN_H_
#define CALC__VALUE_TOKEN_H_

#include "calculator/AbstractToken.h"
#include "calculator/ValueTypes.h"

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
 * Note that in ths implementation, the value stored is mutable, unless `T` is
 * `const`.
 * @tparam T    type of value stored
 */
template <class T>
class ValueToken : public AbstractValueToken {
    static_assert(ValueTypes<T>::ALLOWED && "This type is not supported");

    T value;

   public:
    using type = T; /**< Type of value stored. */

   public:
    /**
     * @brief Constructs with the specified value stored.
     *
     * @param   value   Value to store.
     */
    ValueToken(const T& value) : value{value} {};

    /**
     * @brief Gets the stored value.
     *
     * @return Stored value.
     */
    const T& getValue() const { return value; };

    /**
     * @brief Sets the stored value.
     *
     * @param   newValue    Value to store.
     */
    void setValue(const T& newValue) { value = newValue; }
};

using IntegerToken =
    ValueToken<const ValueT::IntegerT>; /**< Implementation of integers */
using FloatPtToken =
    ValueToken<const ValueT::RealNumT>; /**< Implementation of floating-point
                                           values */

}  // namespace refactor

#endif