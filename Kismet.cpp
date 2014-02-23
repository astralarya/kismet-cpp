#include "Kismet.h"
#include "Prompt.h"

int Kismet::parse(std::istream& istream) {
    std::string line;
    while(std::getline(istream,line)) {
        parseline(line);
    }
    return 0;
}

int Kismet::parse() {
    std::string line;
    while(!_prompt.eof()) {
        line = _prompt.readline();
        parseline(line);
    }
    return 0;
}

int Kismet::parseline(const std::string& line) {
    return 0;
}
