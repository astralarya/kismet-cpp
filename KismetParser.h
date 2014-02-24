// Kismet parser
// Implemented using boost-spirit

#ifndef KISMETPARSER_H
#define KISMETPARSER_H

#include "Roll.h"
#include <boost/spirit/home/qi.hpp>

#undef KismetParser
class KismetParser {
public:
    bool parse(const std::string&);
private:
    struct directive {
        std::string label;
        
    };
    struct die_parser : qi::grammar<Iterator, 
};


#endif // KISMETPARSER_H
