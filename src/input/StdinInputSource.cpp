#include "calculator/StdinInputSource.h"

StdinInputSource::StdinInputSource(std::istream& inStream,
                                   std::ostream& outStream,
                                   std::ostream& errStream)
    : in{inStream}, out{outStream}, err{errStream} {};

InputExpr StdinInputSource::read() {
    err << PROMPT_INPUT;
    return {};
}