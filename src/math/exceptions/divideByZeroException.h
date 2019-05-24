#ifndef MATH__EXCEPTIONS__DIVIDE_BY_ZERO_EXCEPTION_H_
#define MATH__EXCEPTIONS__DIVIDE_BY_ZERO_EXCEPTION_H_

#include "exception.h"

namespace math {

class DivideByZeroException : public Exception {
   public:
    DivideByZeroException(std::string error);
};

}  // namespace math

#endif