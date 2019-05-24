#ifndef CALC__EXCEPT__SYNTAX_EXCEPTION_H_
#define CALC__EXCEPT__SYNTAX_EXCEPTION_H_

#include <exception>
#include <string>

class SyntaxException : public std::exception {
    const std::string STR;

   public:
    SyntaxException(std::string str);

    virtual const char* what() const noexcept override;
};

#endif