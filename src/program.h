#include <iostream>

#ifndef PROGRAM_H
#define PROGRAM_H

namespace cliOptions {
    std::ostream& ostream = std::cout;

    const char TOKEN_VER[] = "version";
    const char TOKEN_HELP[] = "help";
    
    void returnVersion();
    void returnHelp(char *programName);
    void returnIncorrectUsage(char *programName);
}

#endif