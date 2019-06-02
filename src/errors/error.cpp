#include "error.h"

Error::Error(const std::string& tag, const std::string& msg)
    : tag{tag}, msg{msg} {}

Error::Error(std::string&& tag, std::string&& msg) : tag{tag}, msg{msg} {}

Error::Error(const Error& e) : tag{e.tag}, msg{e.msg} {}
Error::Error(Error&& e) : tag{e.tag}, msg{e.msg} {
    e.tag = "";
    e.msg = "";
}

std::string Error::toString() const { return "[Error: " + tag + "] " + msg; }
Error::operator std::string() { return toString(); }

Error& Error::operator=(const Error& e) {
    if (&e == this) return *this;
    tag = e.tag;
    msg = e.msg;
    return *this;
}

Error& Error::operator=(Error&& e) {
    if (&e == this) return *this;
    tag = e.tag;
    msg = e.msg;
    e.tag = "";
    e.msg = "";
    return *this;
}

std::ostream& operator<<(std::ostream& ostream, const Error& e) {
    ostream << e.toString();
}