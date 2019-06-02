#ifndef CALC__ERROR__ERROR_WRAPPED_H_
#define CALC__ERROR__ERROR_WRAPPED_H_

#include "../except/simpleStringException.h"
#include "error.h"

class ErrorCode {
    template <typename R>
    using OnError = R (*)(Error&);

    template <typename R>
    using OnNoError = R (*)(void);

    Error* err;

   public:
    struct NoErrorException : public SimpleStringException {
        NoErrorException();
    };

    ErrorCode();
    ErrorCode(Error&& e);

    ~ErrorCode();

    ErrorCode& operator=(Error&& e);
    void clear();

    bool hasError() const;
    operator bool() const;
    bool operator!() const;

    operator Error() const;
    const Error& get() const;
    const Error& operator*() const;
    const Error& operator->() const;

    std::string toString(const std::string& noError = "") const;
    operator const char*() const;
    operator std::string() const;

    friend std::ostream& operator<<(std::ostream&, const ErrorCode&);

    template <typename R>
    R run(OnNoError<R> onNoErrorCallback, OnError<R> onErrorCallback) {
        if (err == nullptr)
            return onNoErrorCallback();
        else
            return onErrorCallback(*err);
    }
};

#endif