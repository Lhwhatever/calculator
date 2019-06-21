#ifndef CALC__IO_UTILS_H_
#define CALC__IO_UTILS_H_

namespace io {
inline bool isATty(int fileDescriptor);

const bool IS_STDIN_REDIRECTED{isATty(0)};
const bool IS_STDOUT_REDIRECTED{isATty(1)};
};  // namespace io

#endif