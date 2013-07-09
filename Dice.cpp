// Dice.cpp
// Mara Kim
//
// An object that simulates a dice roll

#include "Dice.h"

int Dice::roll(const unsigned int die, const unsigned int times) {
    Dice::roll_type roll;
    roll.die = die;
    roll.times = times;
    return Dice::roll(roll);
}

int Dice::roll(const Dice::roll_type& roll) {
    // prepare random generator
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<unsigned int> distribution(1,roll.die);
    // roll dice
    std::multiset<unsigned int> set;
    for(int i = 0; i < roll.times; i++)
        set.insert(distribution(generator));
    // calculate result
    int result = 0,
        pos = 0,
        top = set.size()-roll.high;
    for(auto it = set.begin(); it != set.end() && pos < top; it++) {
        if(pos >= (roll.low))
            result += *it;
        pos++;
    }
    return result;
}

Dice::result_type Dice::roll_str(const unsigned int die, const unsigned int times) {
    Dice::roll_type roll;
    roll.die = die;
    roll.times = times;
    return Dice::roll_str(roll);
}

Dice::result_type Dice::roll_str(const Dice::roll_type& roll) {
    // prepare random generator
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<unsigned int> distribution(1,roll.die);
    // roll dice
    std::multiset<unsigned int> set;
    for(int i = 0; i < roll.times; i++)
        set.insert(distribution(generator));
    // calculate result
    int result = 0,
        pos = 0,
        top = set.size()-roll.high;
    bool first = true;
    std::stringstream report;
    for(auto it = set.begin(); it != set.end() && pos < top; it++) {
        if(pos >= (roll.low)) {
            if(first)
                first = false;
            else
                report << " + ";
            result += *it;
            report << *it;
        }
        pos++;
    }
    Dice::result_type r;
    r.result = result;
    r.report = report.str();
    return r;
}
