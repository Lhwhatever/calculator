#ifndef CALC__VALUE_TYPES_H_
#define CALC__VALUE_TYPES_H_

/** @ingroup tokens
 * @brief Describes types supported by `ValueToken`.
 *
 * Supported types are:
 * - `ValueTypes<long long>`
 * - `ValueTypes<long double>`
 */
template <class T>
struct ValueTypes {
    /**
     * @brief States whether this type can be stored.
     *
     * |T            |Value  |
     * |:------------|:-----:|
     * |`long long`  |`true` |
     * |`long double`|`true` |
     * |Default      |`false`|
     */
    static constexpr bool ALLOWED{false};
};

#ifndef DOXYGEN_SHOULD_SKIP_THIS

template <>
struct ValueTypes<long long> {
    static constexpr bool ALLOWED{true};
};

template <>
struct ValueTypes<long double> {
    static constexpr bool ALLOWED{true};
};

#endif
#endif