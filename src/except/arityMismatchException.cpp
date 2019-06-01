#include "arityMismatchException.h"

#include <sstream>

ArityMismatchException::ArityMismatchException(std::string identifier,
                                               unsigned int expected,
                                               unsigned int received,
                                               std::string extra)
    : SyntaxException{extra},
      ID{identifier},
      EXPECTED{expected},
      RECEIVED{received} {};

ArityMismatchException::~ArityMismatchException(){};

const char* ArityMismatchException::what() const noexcept {
    std::ostringstream ss{};
    ss << "operator " << ID << " expected " << EXPECTED
       << " arguments but received " << RECEIVED << '.';
    if (MSG != "") ss << "\nOccured: " << MSG;
    return ss.str().c_str();
}