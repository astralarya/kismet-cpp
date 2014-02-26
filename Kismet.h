// Kismet
// Interface to the parser

#ifndef KISMET_H
#define KISMET_H

#include "KismetParser.h"
#include "Prompt.h"
#include "Personality.h"
#include <istream>

class Kismet {
public:
    Kismet():_prompt(),_lastline(),history(){}

    // Interactive prompt
    int parse();

    // Stream parse
    int parse(std::istream&);

private:
    int parseline(const std::string&);

    Prompt _prompt;
    std::string _lastline;
    std::deque<std::string> history; // line history
};

#endif // KISMET_H
