// Personality.h
// Mara Kim
//
// What are you doing here, human?

#ifndef PERSONALITY_H
#define PERSONALITY_H

#include "Options.h"
#include "Dice.h"
#include <string>
#include <iostream>

class Personality {
public:
    static void respond_name();
    static void respond_newline();
    typedef const std::vector<std::string> response_pool;
private:
    static response_pool _name_response;
    static bool _responded;
};

#endif // PERSONALITY_H

