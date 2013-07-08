// Dice.cpp
// Mara Kim
//
// An object that simulates a dice roll

#include "Dice.h"

int Dice::roll(int size, int times) {
    int result = 0;
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_int_distribution distribution(1,size);
    for(int i = 0; i < times; i++)
        result += distribution(generator);
    return result;
}
