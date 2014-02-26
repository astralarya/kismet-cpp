// Personality.h
// Mara Kim
//
// What are you doing here, human?

#ifndef PERSONALITY_H
#define PERSONALITY_H

#include "Options.h"
#include "Dice.h"
#include <string>
#include <boost/regex.hpp>
#include <iostream>
#include <random>
#include <chrono>
#include <functional>

class Personality {
public:
    static void respond_name();
    static void respond_newline();
    static void set_seed(const std::string& seed);
    typedef const std::vector<std::string> response_pool;
private:
    static response_pool _name_response;
    static unsigned int _trigger_count;
    static std::string _seed;
    static boost::regex _matcher;
};

#endif // PERSONALITY_H

