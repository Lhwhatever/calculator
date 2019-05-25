#ifndef MATH__EXCEPTIONS__EXCEPTION_H_
#define MATH__EXCEPTIONS__EXCEPTION_H_

#include <exception>
#include <string>

namespace math {

class Exception : public std::exception {
   private:
    std::string error;

   public:
    Exception(std::string error);

    const char* what() const noexcept;
};

}  // namespace math

#endif