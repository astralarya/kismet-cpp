// Prompt.cpp
// Mara Kim
//
// An object that manages an interactive prompt

#include "Prompt.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

std::string Prompt::_prompt = "> ";
bool Prompt::_ready = false,
     Prompt::_eof = false;
unsigned Prompt::_linecount = 0;

int readline_report(int count, int key) {
    std::string report(Options::Instance()->get(Project::FULL_REPORT));
    if(report.size()) {
        std::cout << '\n' << report << '\n';
        std::cout << rl_prompt;
        Options::Instance()->set(Project::FULL_REPORT,"");
        std::cout << rl_line_buffer << std::flush;
    }
    return 0;
}

void Prompt::_initialize() {
    ::rl_bind_key('\t',readline_report);
    _ready = true;
}

std::string Prompt::readline() {
    // Form prompt
    _linecount++;

    if(!_ready)
        Prompt::_initialize();
    std::string line;
    char* read = ::readline(Prompt::prompt().c_str());
    if(read) {
        auto last_command = ::history_get(::history_length);
        if(*read) {
            // if we have a line, convert to string
            line = read;
            // save to history
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

std::string Prompt::prompt() {
    std::stringstream ss;
    ss << _linecount << _prompt;
    return ss.str();
}
