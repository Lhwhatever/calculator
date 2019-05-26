#include "dataOutOfLimitException.h"

#include <sstream>

DataOutOfLimitException::DataOutOfLimitException(const std::string& t,
                                                 const std::string& l,
                                                 const std::string& v)
    : TYPE{t}, LIMIT{l}, VALUE{v} {}

const char* DataOutOfLimitException::what() const noexcept {
    std::ostringstream ss;
    ss << "cannot store value ";
    if (VALUE != "") ss << VALUE << ' ';
    ss << "in type " << TYPE << "; limit is " << LIMIT;
    return ss.str().c_str();
}