#ifndef CALC__OBSERVER_H_
#define CALC__OBSERVER_H_

#include <memory>

/**
 * @brief Implements the Observer pattern.
 *
 * Note that `Subject` is the type that is passed - for large objects, you may
 * consider making this use `const` reference.
 *
 * @tparam  Type of the subject. This will be passed to `onUpdate()`.
 */
template <typename Subject>
class Observer {
   public:
    Observer() = default;
    virtual ~Observer() = default;
    Observer(const Observer&) = default;
    Observer(Observer&&) = default;
    Observer& operator=(const Observer&) = default;
    Observer& operator=(Observer&&) = default;

    using SubjT = Subject; /**< Type of subject */

    /**
     * @brief Function that is invoked on update.
     *
     * @param   subject     The subject of this observer.
     */
    virtual void onUpdate(Subject subject) = 0;
};

#endif