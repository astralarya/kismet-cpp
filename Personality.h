// Personality.h
// Mara Kim
//
// What are you doing here, human?

#ifndef PERSONALITY_H
#define PERSONALITY_H

#include "Dice.h"
#include <string>
#include <iostream>

class Personality {
public:
    static void respond_name();
    typedef const std::vector<std::string> response_pool;
private:
    static response_pool _name_response;
};

#endif // PERSONALITY_H

