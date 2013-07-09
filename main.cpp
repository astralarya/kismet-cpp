// main.cpp
// Mara Kim

#ifndef PROGRAM_NAME
#define PROGRAM_NAME
#endif
#ifndef SOURCE_VERSION
#define SOURCE_VERSION
#endif
#ifndef REVISION_HASH
#define REVISION_HASH
#endif
#ifndef REVISION_STATUS
#define REVISION_STATUS
#endif

#include "Initializer.h"
#include "Options.h"
#include "KismetParser.h"
#include <iostream>


inline void printshorthelp()
{
    // output usage info
    std::cout << "Usage: " << PROGRAM_NAME << '\n';
}

void printhelp()
{
    // output help
    printshorthelp();
    std::cout << "<Description>\n"
              << "Option\t\tGNU long option\t\tMeaning\n"
              << "-r\t\t--reactive\t\t\tReactive mode\n"
              << "-h, -?\t\t--help\t\t\tShow this message\n"
              << "-v\t\t--version\t\tOutput program version\n"
              << "-V\t\t--version-long\t\tOutput full program version\n";
}

void printversion()
{
    std::cout << PROGRAM_NAME << ' ' << SOURCE_VERSION << std::endl;
}

void printrevision()
{
    std::cout << REVISION_HASH << std::endl
              << REVISION_STATUS << std::endl;
}

int main(int argc, const char* argv[])
{

    // Initialize
    Initializer init(argc, argv);

    // process arguments
    bool stop = false;
    if(init.flag("version") ||
       init.flag('v') ) {
        // output version
        printversion();
        stop = true;
    }
    if(init.flag("version-long") ||
       init.flag('V') ) {
        // output revision
        printversion();
        printrevision();
        stop = true;
    }
    if(init.flag("help") ||
       init.flag('h') ||
       init.flag('?')) {
        printhelp();
        stop = true;
    }
    if(init.flag("reactive") ||
       init.flag('r') ) {
        // set reactive
        Options::Instance()->set(REACTIVE,true);
    }

    if(stop) {
        return 0;
    }

    // Greet interactive
    if(Options::Instance()->get(INTERACTIVE))
        std::cout << "Greetings, human!\n"
                     "I am Kismet. Input a roll and press ENTER.\n"
                     "CTRL-D to exit.\n"
                     ">" << std::flush;

    // run program
    KismetParser kismet;
    kismet.parse();

    // close interactive
    if(Options::Instance()->get(INTERACTIVE))
        std::cout << "exit" << std::endl;

    return 0;
}
