#ifndef CALC__ABSTRACT_FUNCTION_TOKEN_H_
#define CALC__ABSTRACT_FUNCTION_TOKEN_H_

#include "AbstractToken.h"

/**
 * @brief Represents functions and operators.
 *
 * This class represents any function or operator in a mathematical expression,
 * with the exception of grouping operators such as parentheses).
 *
 */
class AbstractFunctionToken : public AbstractToken {};

#endif