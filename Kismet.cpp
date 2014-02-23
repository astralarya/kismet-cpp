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
        if(line.empty()) {
            if(_lastline.size())
                parseline(_lastline);
        } else {
            parseline(line);
            _lastline = line;
        }
    }
    return 0;
}

int Kismet::parseline(const std::string& line) {

    std::cout << std::endl;
    

    return 0;
}
