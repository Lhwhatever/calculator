#include "divideByZeroException.h"

namespace math {

DivideByZeroException::DivideByZeroException(std::string error)
    : Exception{error} {}

}  // namespace math