// Kismet parser
// Implemented using boost-spirit

#ifndef KISMET_H
#define KISMET_H

#include "Prompt.h"
#include <istream>
#include <boost/spirit/home/qi.hpp>

class Kismet {
public:
    int parse(std::istream&);
    int parse();
private:
    int parseline(const std::string&);
    Prompt _prompt;
};

#endif // KISMET_H
