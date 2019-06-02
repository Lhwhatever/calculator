#include "errorWrapped.h"

ErrorCode::NoErrorException::NoErrorException()
    : SimpleStringException{"no error in errorcode"} {}

ErrorCode::ErrorCode() : err{nullptr} {}
ErrorCode::ErrorCode(Error&& e) : err{new Error(e)} {}

ErrorCode::~ErrorCode() {
    if (err != nullptr) delete err;
}

ErrorCode& ErrorCode::operator=(Error&& e) {
    if (err == nullptr) {
        err = new Error(e);
    } else {
        err->tag = e.tag;
        err->msg = e.msg;
        e.tag = "";
        e.msg = "";
    }
    return *this;
}

void ErrorCode::clear() {
    if (err == nullptr) return;
    delete err;
    err = nullptr;
}

bool ErrorCode::hasError() const { return err != nullptr; }
ErrorCode::operator bool() const { return err != nullptr; }
bool ErrorCode::operator!() const { return err == nullptr; }

ErrorCode::operator Error() const {
    if (err == nullptr) throw ErrorCode::NoErrorException();
    return *err;
}

const Error& ErrorCode::get() const {
    if (err == nullptr) throw ErrorCode::NoErrorException();
    return *err;
}

const Error& ErrorCode::operator*() const {
    if (err == nullptr) throw ErrorCode::NoErrorException();
    return *err;
}

const Error& ErrorCode::operator->() const {
    if (err == nullptr) throw ErrorCode::NoErrorException();
    return *err;
}

std::string ErrorCode::toString(const std::string& noError) const {
    if (err == nullptr) return noError;
    return err->toString();
}

ErrorCode::operator const char*() const {
    if (err == nullptr) return "";
    return err->toString().c_str();
}

ErrorCode::operator std::string() const {
    if (err == nullptr) return "";
    return err->toString();
}

std::ostream& operator<<(std::ostream& ostream, const ErrorCode& e) {
    ostream << *e.err;
    return ostream;
}