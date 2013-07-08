// Dice.h
// Mara Kim
//
// An object that simulates a dice roll

#ifndef DICE_H
#define DICE_H

#include <random>
#include <chrono>
#include "Options.h"

class Dice {
public:
    static int roll(int size, int times);
}

#endif // DICE_H
