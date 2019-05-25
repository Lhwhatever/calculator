#include "exception.h"

namespace math {
Exception::Exception(std::string error) : error{error} {}

const char* Exception::what() const noexcept { return error.c_str(); }
}