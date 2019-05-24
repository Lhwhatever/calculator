#include "arityMismatchException.h"

#include <sstream>

ArityMismatchException::ArityMismatchException(std::string identifier,
                                               int expected, int received,
                                               std::string extra)
    : ID{identifier}, EXPECTED{expected}, RECEIVED{received}, EXTRA{extra} {};

ArityMismatchException::~ArityMismatchException(){};

const char* ArityMismatchException::what() const noexcept {
    std::ostringstream ss{};
    ss << "Arity mismatch: operator " << ID << " expected " << EXPECTED
       << " arguments but received " << RECEIVED << '.';
    if (EXTRA != "") ss << "\nError at: " << EXTRA;
    return ss.str().c_str();
}