// main.cpp
// A main function that reports help and version info 
//
// Copyright (C) 2013 Mara Kim
//
// This program is free software: you can redistribute it and/or modify it under
// the terms of the GNU General Public License as published by the Free Software
// Foundation, either version 3 of the License, or (at your option) any later
// version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
// details.
//
// You should have received a copy of the GNU General Public License along with
// this program. If not, see http://www.gnu.org/licenses/.


#include "Initializer.h"
#include "Options.h"
#include "KismetParser.h"
#include <iostream>

int main(int argc, char** argv) {
    // Initialize
    // argcount, argvector, argument usage, description
    Initializer init(argc, argv, 0,
                     "Dice roller with personality");

    // Describe options
    init.option("reactive", 'r', 0, "Reactive mode: wait for ..[] attention sequence; Default non-interactive",
                [&] (char* arg, Initializer::state* state) -> int {
                    Options::Instance()->set(Project::REACTIVE,true);
                    Options::Instance()->set(Project::INTERACTIVE,false);
                    return 0;
                });
    init.option("non-interactive", 'n', 0, "Non-interactive mode",
                [&] (char* arg, Initializer::state* state) -> int {
                    // set non-interactive, depersonalize
                    Options::Instance()->set(Project::INTERACTIVE,false);
                    Options::Instance()->set(Project::PERSONALITY,false);
                    return 0;
                });
    init.event(Initializer::END, // Check argument count
               [&] (char* arg, Initializer::state* state) -> int {
                   if(state->arg_num < 2)
                       Initializer::usage(state);
                   return 0;
               });

    // Parse arguments
    init.parse();

    // Greet interactive
    if(Options::Instance()->get(Project::INTERACTIVE))
        std::cout << "Greetings, human! I am Kismet <3\n"
                     "Input a roll and press ENTER.\n"
                     "Exit with 'exit' or CTRL-D." << std::endl;

    // run program
    KismetParser kismet;
    kismet.parse();

    // close interactive
    if(Options::Instance()->get(Project::INTERACTIVE))
        std::cout << "exit" << std::endl;

    return 0;
}
