#ifndef CALC__TOKEN_EMPLACER_FOR_INLINE_H_
#define CALC__TOKEN_EMPLACER_FOR_INLINE_H_

#include "calculator/AbstractTokenEmplacer.h"

/**
 * @brief Emplacement for a sequence of tokens from Reverse Polish Notation.
 *
 * Implements an algorithm that emplaces tokens in the correct sequence given
 * that they arrived from RPN.
 */
class TokenEmplacerForRpn : public AbstractTokenEmplacer {
   public:
    /**
     * @brief Resets to the newly-constructed state.
     *
     * Empties the working queue so if `extract()` is called subsequently, an
     * empty `TokenQueue` will be returned.
     */
    virtual void reset() override;

    /**
     * @brief Places one token.
     *
     * @param   token   An owning pointer to the token.
     */
    virtual void emplace(TokenPtr token) override;

    /**
     * @brief Returns the working queue and then empties the working queue.
     *
     * @return  A queue of all the tokens that have been emplaced since the last
     * call to `reset()` or `extract()`.
     */
    virtual TokenQueue extract() override;
};

#endif