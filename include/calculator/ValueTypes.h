#ifndef CALC__VALUE_TYPES_H_
#define CALC__VALUE_TYPES_H_

#include "calculator/ValueT.h"

template <class Type, class ComparedAgainst>
struct EnableIf : std::enable_if<std::is_same_v<ComparedAgainst, Type> ||
                                 std::is_same_v<ComparedAgainst, const Type>> {
};

template <class Type, class ComparedAgainst>
using EnableIfT = typename EnableIf<Type, ComparedAgainst>::type;

/**
 * @brief Describes types supported by `ValueToken`.
 *
 * Supported types can be found inside the namespace `ValueT`.
 */
template <class T, class = void>
struct ValueTypes {
    using Type = std::remove_const_t<T>;

    ValueTypes() = delete; /**< Construction of this struct is not allowed. */

    /**
     * @brief States whether this type can be stored.
     *
     * |T                 |Value  |
     * |:-----------------|:-----:|
     * |`ValueT::IntegerT`|`true` |
     * |`ValueT::RealNumT`|`true` |
     * |Default           |`false`|
     */
    static constexpr bool ALLOWED{false};
};

template <class T>
struct ValueTypes<T, EnableIfT<ValueT::IntegerT, T>> {
    static constexpr bool ALLOWED{true};
};

template <class T>
struct ValueTypes<T, EnableIfT<ValueT::RealNumT, T>> {
    static constexpr bool ALLOWED{true};
};

#endif