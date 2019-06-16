#include <type_traits>

/**
 * @brief Namespace for all variable containers.
 *
 */
namespace containers {

/**
 * @brief Nested namespace for the generic variants of all variable containers.
 *
 */
namespace generic {

/**
 * @brief Container for a real number.
 *
 * @tparam StorageType type for floating point used.
 * `std::is_floating_point<StorageType>::value` must be `true`.
 */
template <class StorageType, class = void>
class RealContainer {
    static_assert(std::is_floating_point<StorageType>::value);

    /**
     * @brief Gets the real value stored.
     *
     * @return Real value stored.
     */
    virtual StorageType getRealValue() const = 0;
};

/**
 * @brief Partial specialization for containers of modifiable values.
 *
 */
template <class StorageType>
class RealContainer<StorageType,
                    std::enable_if<std::is_const<StorageType>::value>> {
    /**
     * @brief Sets the value stored.
     *
     * @return Real value stored.
     *
     */
    virtual void setRealValue(StorageType newValue) = 0;
};

}  // namespace generic

template <bool modifiable>
using RealContainer =
    generic::RealContainer<modifiable ? long double : const long double>;

}  // namespace containers