#ifndef CALC__ABSTRACT_TOKEN_EMPLACER_H_
#define CALC__ABSTRACT_TOKEN_EMPLACER_H_

#include <deque>
#include <memory>

#include "calculator/AbstractToken.h"

using TokenPtr = std::shared_ptr<AbstractToken>; /**< Alias for an owning
                                                    pointer to a token */
using TokenQueue =
    std::deque<TokenPtr> /**< Alias for a queue containing tokens */;

/**
 * @brief Represents an algorithm to emplace tokens
 *
 */
class AbstractTokenEmplacer {
   public:
    AbstractTokenEmplacer() = default;          /**< Default constructor */
    virtual ~AbstractTokenEmplacer() = default; /**< Default destructor */

    AbstractTokenEmplacer(const AbstractTokenEmplacer&) =
        default; /**< Default copy constructor */

    AbstractTokenEmplacer(AbstractTokenEmplacer&&) =
        default; /**< Default move constructor */

    AbstractTokenEmplacer& operator=(const AbstractTokenEmplacer&) =
        default; /**< Default copy assignment operator */

    AbstractTokenEmplacer& operator=(AbstractTokenEmplacer&&) =
        default; /**< Default move assignment operator */

    /**
     * @brief Resets to the newly-constructed state.
     *
     * If this member function is called, the next call to `extract()` will
     * return an empty `TokenQueue`.
     */
    virtual void reset() = 0;

    /**
     * @brief Places one token.
     *
     * @param   token   An owning pointer to the token.
     */
    virtual void emplace(TokenPtr&& token) = 0;

    /**
     * @brief Returns the queue after tokenizing.
     *
     * @return  A queue of all the tokens that have been emplaced since the last
     * call to `reset()` or `extract()`.
     */
    virtual TokenQueue extract() = 0;
};

#endif