#include "calculator/IOUtils.h"

#if defined(_WIN32) || defined(__MINGW32__)
#define IS_WINDOWS
#endif

#if defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
#define IS_POSIX
#include <unistd.h>
#endif

namespace {
bool isATty(int fileDescriptor) {
#ifdef IS_WINDOWS
    return _isatty(fileDescriptor);
#elif defined(IS_POSIX)
    return isatty(fileDescriptor) == 1;
#else
    return true;
#endif
}
}  // namespace

const bool io::IS_STDIN_REDIRECTED{isATty(0)};
const bool io::IS_STDOUT_REDIRECTED{isATty(1)};