#ifndef CALC__ABSTRACT_INPUT_SOURCE_H_
#define CALC__ABSTRACT_INPUT_SOURCE_H_

#include <string_view>

using InputExpr =
    std::string_view; /**< Alias for an expression read from input. */

/**
 * @brief Represents a source of input for the program.
 *
 */
class AbstractInputSource {
    /**
     * @brief Reads a line of input.
     *
     * @return The line of input read.
     */
    virtual InputExpr read() = 0;
};
#endif