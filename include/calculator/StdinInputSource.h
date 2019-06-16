#ifndef CALC__STDIN_INPUT_SOURCE_H_
#define CALC__STDIN_INPUT_SOURCE_H_

#include <iostream>
#include <string>

#include "calculator/AbstractInputSource.h"

/**
 * @brief An input source using stdin.
 *
 */
class StdinInputSource : public AbstractInputSource {
    std::istream& in;
    std::ostream& out;
    std::ostream& err;

    static constexpr std::string_view PROMPT_INPUT{"> "};
    static constexpr std::string_view PROMPT_CONTINUE{"... "};

   public:
    /**
     * @brief Constructs the input source using the given streams as input and
     * output.
     *
     * Note: should supply your own streams only for testing use.
     *
     * @param   in  Input stream (e.g. stdin). Default is `std::cin`.
     * @param   out Output stream (e.g. stdout). Default is `std::cout`.
     * @param   err Stream for errors (e.g. stderr). Default is `std::cerr`.
     */
    StdinInputSource(std::istream& in = std::cin, std::ostream& out = std::cout,
                     std::ostream& err = std::cerr);

    /**
     * @brief Reads a line of input from stdin.
     *
     * Reads until the next `\n` token.
     * A newline can be escaped by a backslash. I.e. if the last character
     * of the line is a backslash, this will continue reading input.
     */
    virtual InputExpr read() override;
};

#endif