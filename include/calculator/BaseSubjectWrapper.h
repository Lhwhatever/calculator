#ifndef CALC__BASE_SUBJECT_WRAPPER_H_
#define CALC__BASE_SUBJECT_WRAPPER_H_

#include "calculator/Observer.h"

/**
 * @brief Assists in implementing the Observer pattern.
 *
 * Subclass this and implement the various pure virtual functions.
 */
template <typename Subject, typename SubjPassType = const Subject&>
class BaseSubjectWrapper {
   protected:
    using ObserverPtr = std::weak_ptr<Observer<SubjPassType>>;

   public:
    BaseSubjectWrapper() = default;
    virtual ~BaseSubjectWrapper() = default;
    BaseSubjectWrapper(const BaseSubjectWrapper&) = default;
    BaseSubjectWrapper(BaseSubjectWrapper&&) = default;
    BaseSubjectWrapper& operator=(const BaseSubjectWrapper&) = default;
    BaseSubjectWrapper& operator=(BaseSubjectWrapper&&) = default;

    using SubjT = Subject; /**< Type of subject */
    using SubjPassT =
        SubjPassType; /**< Type by which subject is passed to observers */

    /**
     * @brief Registers the given observer.
     *
     * @param   observer    Non-owning weak pointer to the observer.
     */
    virtual void addObserver(ObserverPtr observer) = 0;

    /**
     * @brief Updates all the observers when the subject is updated.
     *
     */
    virtual void updateObservers() = 0;
};

#endif