#ifndef PROGRAM_H

#define PROGRAM_H
#define PROGRAM_VERSION "0.2"

namespace cliOptions {
    void returnVersion();
    void returnHelp(char *programName);
    void returnIncorrectUsage(char *programName);
}

#endif