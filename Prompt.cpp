// Prompt.cpp
// Mara Kim
//
// An object that manages an interactive prompt

#include "Prompt.h"
#include <readline/readline.h>
#include <readline/history.h>

bool Prompt::_ready = false;
bool Prompt::_eof = false;

void Prompt::_initialize() {
    ::rl_bind_key('\t',rl_insert);
    _ready = true;
}

std::string Prompt::readline(const std::string& prompt) {
    if(!_ready)
        Prompt::_initialize();
    std::string line;
    char* read = ::readline(prompt.c_str());
    if(read && *read) {
        // if we have a line save to history
        ::add_history(read);
        line = read;
    }
    if(read)
        free(read);
    else
        _eof = true;
    return line;
}

bool Prompt::eof() {
    return _eof;
}
