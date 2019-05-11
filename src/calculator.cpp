#include <iostream>
#include <cstring>

#include "h/input.h"
#include "h/program.h"

int main(int argc, char* argv[]) {
    if(argc == 1) {
        std::cout << "Calculator application, command line.\n";
        cliOptions::returnVersion();

        std::string expr { getNextExpr() };
        std::cout << "You entered " << expr << "\n";
    } else for(int i = 1; i < argc; i++) {

        const char TOKEN_VER[] = "version";
        const char TOKEN_HELP[] = "help";


        if(*argv[i] == '-') { // entered options
            if(*(++argv[i]) == '-') { // full word
                ++argv[i];

                if(!strcmp(argv[i], TOKEN_VER)) cliOptions::returnVersion();
                if(!strcmp(argv[i], TOKEN_HELP)) cliOptions::returnHelp(argv[0]);
            } else if(*argv[i] == 'v' || *argv[i] == 'V') cliOptions::returnVersion();
            else if(*argv[i] == 'h' || *argv[i] == 'H') cliOptions::returnHelp(argv[0]);
            else cliOptions::returnIncorrectUsage(argv[0]);
        } // entered cmd line argument
        else cliOptions::returnIncorrectUsage(argv[0]);
    }
    
    return 0;
}

namespace cliOptions {
    void returnVersion() {
        std::cout << "Version " PROGRAM_VERSION;
    }

    void returnHelp(char *programName) {
        std::cout << "Usage: " << programName << " [options]\n"
                     "\n"
                     "Possible options: \n"
                     "--version, -v, -V     Show version of application.\n"
                     "--help, -h, -H        Show this help message.\n";
    }

    void returnIncorrectUsage(char *programName) {
        std::cout << "Usage: " << programName << " [-v] [-h]\n"
                     "Run " << programName << " -h to see more help for this program.\n";
    }
}