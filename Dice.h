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
#include "Options.h"

class Dice {
public:
    typedef std::pair<int,std::string> result_type;
    struct roll_type {
        unsigned int die;
        unsigned int times;
    };

    static int roll(const unsigned int& die, const unsigned int& times);
    static int roll(const roll_type& roll);
    static result_type roll_str(const unsigned int& die, const unsigned int& times);
    static result_type roll_str(const roll_type& roll);
};

class Roll {
};
#endif // DICE_H
