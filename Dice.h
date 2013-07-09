// Dice.h
// Mara Kim
//
// An object that simulates a dice roll

#ifndef DICE_H
#define DICE_H

#include <random>
#include <chrono>
#include <utility>
#include <string>
#include <sstream>
#include <set>
#include <map>
#include "Options.h"

class Dice {
public:
    struct result_type {
        std::string report;
        int result;
    };
    struct roll_type {
        unsigned int die;
        unsigned int times;
        unsigned int high;
        unsigned int low;
        roll_type():
        die(Options::Instance()->get(DEFAULT_DIE)),
        times(0),
        high(0),
        low(0) {}
    };

    static int roll(const unsigned int die, const unsigned int times);
    static int roll(const roll_type& roll);
    static result_type roll_str(const unsigned int die, const unsigned int times);
    static result_type roll_str(const roll_type& roll);
};

#endif // DICE_H
