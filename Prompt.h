// Prompt.h
// Mara Kim
//
// An object that manages an interactive prompt

#ifndef PROMPT_H
#define PROMPT_H

#include "Options.h"
#include <string>
#include <iostream>

class Prompt {
public:
    static std::string readline();
    static bool eof();
private:
    static std::string prompt();

    static std::string _prompt;
    static bool _ready;
    static bool _eof;
    static void _initialize();
    static unsigned _linecount;
};

#endif // PROMPT_H
