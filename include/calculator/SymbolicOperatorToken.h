#ifndef CALC__SYMBOLIC_OPERATOR_TOKEN_H_
#define CALC__SYMBOLIC_OPERATOR_TOKEN_H_

#include <string>

#include "calculator/AbstractFunctionToken.h"

/**
 * @brief Represents operators that can be represented by a symbol (e.g. +, -).
 *
 */
class SymbolicOperatorToken : public AbstractFunctionToken {
   public:
    const std::string_view symbol; /**< Symbol */

   public:
    /**
     * @brief Construct a token with the given symbol.
     *
     * @param   symbol  symbol of the token
     */
    SymbolicOperatorToken(std::string_view symbol);
};

#endif