#include "noOperationException.h"

NoOperationException::NoOperationException(std::string msg) : MSG{msg} {}
NoOperationException::~NoOperationException() {}

const char* NoOperationException::what() const noexcept { return MSG.c_str(); }