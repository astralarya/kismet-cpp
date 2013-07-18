// Prompt.h
// Mara Kim
//
// An object that manages an interactive prompt

#include "Options.h"
#include <string>
#include <iostream>

class Prompt {
public:
    static std::string readline(const std::string& prompt);
    static bool eof();
private:
    static bool _ready;
    static bool _eof;
    static void _initialize();
};
