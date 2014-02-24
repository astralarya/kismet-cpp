// Kismet
// Interface to the parser

#ifndef KISMET_H
#define KISMET_H

#include "Prompt.h"
#include <istream>

class Kismet {
public:
    Kismet():_prompt(),_lastline(){}

    // Interactive prompt
    int parse();

    // Stream parse
    int parse(std::istream&);

private:
    int parseline(const std::string&);

    Prompt _prompt;
    std::string _lastline;
};

#endif // KISMET_H
