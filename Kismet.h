// Kismet parser
// Implemented using boost-spirit

#include <istream>
#include <boost/spirit/home/qi.hpp>

class Kismet {
public:
    int parse(std::istream& = std::cin);
};
