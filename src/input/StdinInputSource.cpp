#include "calculator/StdinInputSource.h"

StdinInputSource::StdinInputSource(std::istream& inStream,
                                   std::ostream& outStream,
                                   std::ostream& errStream)
    : in{inStream}, out{outStream}, err{errStream} {};

InputExpr StdinInputSource::read() {
    err << PROMPT_INPUT;
    std::string expr;

    while (true) {
        std::string nextLine;
        std::getline(in, nextLine);
        expr += nextLine;

        if (expr.back() != '\\') break;  // no escaped newline
        expr.pop_back();                 // escaped newline
        err << PROMPT_CONTINUE;
    }

    in.clear();

    return expr.c_str();
}