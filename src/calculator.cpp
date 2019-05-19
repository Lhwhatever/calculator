#include <cstring>

#include "program.h"
#include "session.h"
#include "settings.h"

int main(int argc, char* argv[]) {
    if (argc == 1) {
        std::cout << "Calculator application, command line.\n";
        cliOptions::returnVersion();

        Session ss;
        ss.rep();
        std::cout << "End of Program";
    } else
        for (auto i{1}; i < argc; i++) {
            using namespace cliOptions;

            if (*argv[i] == '-') {          // entered options
                if (*(++argv[i]) == '-') {  // full word
                    ++argv[i];

                    if (!strcmp(argv[i], TOKEN_VER)) returnVersion();
                    if (!strcmp(argv[i], TOKEN_HELP)) returnHelp(argv[0]);
                } else if (*argv[i] == 'v' || *argv[i] == 'V')
                    returnVersion();
                else if (*argv[i] == 'h' || *argv[i] == 'H')
                    returnHelp(argv[0]);
                else
                    returnIncorrectUsage(argv[0]);
            } else
                returnIncorrectUsage(argv[0]);
        }

    return 0;
}

namespace cliOptions {
void returnVersion() {
#ifdef VERSION_STRING
    ostream << "Version " << VERSION_STRING;
#else
    ostream << "Unknown version";
#endif

#ifdef DEBUG
    ostream << " (debug)\n";
#else
    ostream << "\n";
#endif
}

void returnHelp(char* programName) {
    ostream << "Usage: " << programName
            << " [options]\n"
               "\n"
               "Possible options: \n"
               "--version, -v, -V     Show version of application.\n"
               "--help, -h, -H        Show this help message.\n";
}

void returnIncorrectUsage(char* programName) {
    ostream << "Usage: " << programName
            << " [-v] [-h]\n"
               "Run "
            << programName << " -h to see more help for this program.\n";
}
}  // namespace cliOptions