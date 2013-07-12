// Prompt.cpp
// Mara Kim
//
// An object that manages an interactive prompt

#include "Prompt.h"
#include <stdio.h>
#include <string>
#include <readline/readline.h>
#include <readline/history.h>
#include <iostream>

bool Prompt::_ready = false;
bool Prompt::_eof = false;

int readline_exit(int count, int key) {
    rl_replace_line("exit",0);
    rl_done = 1;
    return 0;
}

void Prompt::_initialize() {
    ::rl_bind_key('\t',rl_insert);
    ::rl_bind_key('',readline_exit);
    _ready = true;
}

std::string Prompt::readline(const std::string& prompt) {
    if(!_ready)
        Prompt::_initialize();
    std::string line;
    char* read = ::readline(prompt.c_str());
    if(read) {
        auto last_command = ::history_get(::history_length);
        if(*read) {
            // if we have a line save to history
            line = read;
            if(last_command) {
                if(line != std::string(last_command->line))
                    ::add_history(read);
            } else
                ::add_history(read);
        } else if(last_command)
            line = last_command->line;
        free(read);
    } else
        _eof = true;
    return line;
}

bool Prompt::eof() {
    return _eof;
}
