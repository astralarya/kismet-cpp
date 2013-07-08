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
        int die;
        int times;
    };

    static int roll(const int& die, const int& times);
    static int roll(const roll_type& roll);
    static result_type roll_str(const int& die, const int& times);
    static result_type roll_str(const roll_type& roll);
};

#endif // DICE_H
