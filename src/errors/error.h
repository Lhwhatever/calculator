#ifndef CALC__ERRORS__ERROR_H_
#define CALC__ERRORS__ERROR_H_

#include <iostream>
#include <string>

struct Error {
    std::string tag;
    std::string msg;

   protected:
    Error(const std::string& tag, const std::string& msg);
    Error(std::string&& tag, std::string&& msg);

   public:
    Error(const Error& e);
    Error(Error&& e);

    std::string toString() const;
    operator std::string();

    Error& operator=(const Error& e);
    Error& operator=(Error&& e);

    friend std::ostream& operator<<(std::ostream&, const Error& e);
};

#endif