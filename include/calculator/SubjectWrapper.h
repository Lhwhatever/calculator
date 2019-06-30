#ifndef CALC__SUBJECT_WRAPPER_H_
#define CALC__SUBJECT_WRAPPER_H_

#include <list>

#include "calculator/BaseSubjectWrapper.h"

/**
 * @brief Provides a simple implementation of `BaseSubjectWrapper`.
 *
 * @tparam  Subject     Type of the subject.
 * @tparam  SubjPassType     Type of subject to pass to `Observer::onUpdate()`.
 */
template <typename Subject, typename SubjPassType = const Subject&>
class SubjectWrapper : public BaseSubjectWrapper<Subject, SubjPassType> {
    using SuperT = BaseSubjectWrapper<Subject, SubjPassType>;

   protected:
    std::list<std::weak_ptr<Observer<SubjPassType>>>
        observers; /**< Registered observers */

   public:
    Subject subject; /**< Wrapped instance of Subject. */

    /**
     * @brief Constructs, moving the given `Subject` instance in.
     *
     * `Subject` must implement a move constructor. This then takes ownership of
     * `subj`.
     *
     * @param   subj    Instance of `Subject` to be wrapped and taken ownership
     * of.
     */
    SubjectWrapper(Subject&& subj) : subject{subj} {}

    /**
     * @brief Registers the given observer.
     *
     * Note that nothing will occur if the pointer to the observer has expired.
     *
     * @param   observer            Non-owning weak pointer to the observer.
     * @param   updateObserverNow   Whether observer should be updated now.
     */
    virtual void addObserver(typename SuperT::ObserverPtr observer,
                             bool updateObserverNow) override {
        if (observer.expired()) return;
        observers.push_back(observer);
        if (updateObserverNow) observer->lock()->onUpdate(subject);
    }

    /**
     * @brief Updates all the observers when subject is updated.
     *
     * Observers are updated in order of insertion. Any expired observers are
     * cleared from the list.
     */
    virtual void updateObserver() override {
        for (auto it{begin(observers)}, end{end(observers)}; it < end; ++it) {
            if (it->expired())
                observers.erase(--it + 1);
            else
                it->lock()->onUpdate(subject);
        }
    }
};

#endif