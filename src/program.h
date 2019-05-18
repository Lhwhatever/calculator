#ifndef PROGRAM_H_
#define PROGRAM_H_


#include <iostream>


namespace cliOptions {
    std::ostream& ostream = std::cout;

    constexpr char TOKEN_VER[] = "version";
    constexpr char TOKEN_HELP[] = "help";

    void returnVersion();
    void returnHelp(char* programName);
    void returnIncorrectUsage(char* programName);
}


#endif