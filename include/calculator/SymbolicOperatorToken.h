#ifndef CALC__SYMBOLIC_OPERATOR_TOKEN_H_
#define CALC__SYMBOLIC_OPERATOR_TOKEN_H_

#include <string>

#include "calculator/AbstractFunctionToken.h"

/**
 * @brief Represents operators that can be represented by a symbol (e.g. +, -).
 *
 */
class SymbolicOperatorToken : public AbstractFunctionToken {
    const std::string symbol;

   public:
    /**
     * @brief Creates a token with the given symbol.
     *
     * @param[in]   symbol  symbol of the token
     */
    SymbolicOperatorToken(const std::string& symbol);

    /**
     * @brief Gets the symbol of this token.
     *
     * @returns Symbol of the token.
     */
    const std::string& getSymbol() const;
};

#endif