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

void printhelp() {
    // output help
    printshorthelp();
    std::cout << "<Description>\n"
                 "Option\t\tGNU long option\t\tMeaning\n"
                 "-r\t\t--reactive\t\tReactive mode: wait for ..[] attention sequence; Default non-interactive\n"
                 "-n\t\t--non-interactive\tNon-interactive mode\n"
                 "-i\t\t--interactive\t\tForce interactive mode\n"
                 "-h, -?\t\t--help\t\t\tShow this message. Secrets?\n"
                 "-v\t\t--version\t\tOutput program version\n";
}

void printsecrets() {
    printhelp();
    std::cout << "-p\t\t--personality\t\tActivate personality\n"
                 "-V\t\t--version-long\t\tOutput full program version\n";
}

void printversion() {
    std::cout << PROGRAM_NAME << ' ' << SOURCE_VERSION << std::endl;
}

void printrevision() {
    std::cout << REVISION_HASH << std::endl
              << REVISION_STATUS << std::endl;
}

int main(int argc, const char* argv[]) {

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
       init.flag('h')) {
        printhelp();
        stop = true;
    }
    if(init.flag('?')) {
        printsecrets();
        stop = true;
    }
    if(init.flag("reactive") ||
       init.flag('r') ) {
        // set reactive
        Options::Instance()->set(REACTIVE,true);
        Options::Instance()->set(INTERACTIVE,false);
    }
    if(init.flag("non-interactive") ||
       init.flag('n') ) {
        // set non-interactive, depersonalize
        Options::Instance()->set(INTERACTIVE,false);
        Options::Instance()->set(PERSONALITY,false);
    }
    if(init.flag("personality") ||
       init.flag('p') ) {
        Options::Instance()->set(PERSONALITY,true);
    }
    if(init.flag("interactive") ||
       init.flag('i') ) {
        // set interactive
        Options::Instance()->set(INTERACTIVE,true);
    }

    if(stop) {
        return 0;
    }

    // Greet interactive
    if(Options::Instance()->get(INTERACTIVE))
        std::cout << "Greetings, human! I am Kismet <3\n"
                     "Input a roll and press ENTER.\n"
                     "Exit with 'exit' or CTRL-D." << std::endl;

    // run program
    KismetParser kismet;
    kismet.parse();

    // close interactive
    if(Options::Instance()->get(INTERACTIVE))
        std::cout << "exit" << std::endl;

    return 0;
}
