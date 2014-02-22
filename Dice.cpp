// Dice.cpp
// Mara Kim
//
// An object that simulates a dice roll

#include "Dice.h"

// Global static pointer that ensures a single instance
Dice::generator* Dice::_Instance = NULL;

// Function call to return instance of this class
Dice::generator& Dice::Generator() {
    if(!_Instance) // if there is no instance
    {
        unsigned seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        _Instance = new std::default_random_engine(seed);
    }

    return *_Instance;
}

int Dice::roll(const unsigned int die, const unsigned int times) {
    Dice::roll_type roll;
    roll.die = die;
    roll.times = times;
    return Dice::roll(roll);
}

int Dice::roll(const Dice::roll_type& roll) {
    // prepare random generator
    std::uniform_int_distribution<unsigned int> distribution(1,roll.die);
    // roll dice
    std::multiset<unsigned int> set;
    for(unsigned int i = 0; i < roll.times; i++)
        set.insert(distribution(Dice::Generator()));
    // calculate result
    int result = 0;
    unsigned int pos = 0,
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
    // roll dice
    result_set value = Dice::roll_set(roll);
    // construct report
    int result = 0;
    std::stringstream report;
    bool first = true;
    for(auto it = value.rolls.begin(); it != value.rolls.end(); it++) {
            if(first)
                first = false;
            else
                report << " + ";
            result += (*it);
            report << (*it);
    }
    first = true;
    for(auto it = value.drops.begin(); it != value.drops.end(); it++) {
            if(first) {
                report << " ~ ";
                first = false;
            } else
                report << ' ';
            report << (*it);
    }
    Dice::result_type r;
    r.result = result;
    r.report = report.str();
    return r;
}

Dice::result_set Dice::roll_set(const Dice::roll_type& roll) {
    // roll dice, recording order
    std::multimap<unsigned int,unsigned int> rolls, // map of results to roll order
                                             keep, // map of roll order to results
                                             drop; // map of roll order to results
    std::uniform_int_distribution<unsigned int> distribution(1,roll.die);
    for(unsigned int i = 0; i < roll.times; i++)
        rolls.insert(std::pair<unsigned int, unsigned int>(distribution(Dice::Generator()),i));
    // perform drops
    int pos = 0,
        top = rolls.size()-roll.high;
    for(auto it = rolls.begin(); it != rolls.end(); it++) {
        if(pos >= (roll.low) && pos < top)
            keep.insert(std::pair<unsigned int, unsigned int>(it->second,it->first));
        else
            drop.insert(std::pair<unsigned int, unsigned int>(it->second,it->first));
        pos++;
    }
    // construct sets
    Dice::result_set r;
    for(auto it = keep.begin(); it != keep.end(); it++) {
            r.rolls.push_back(it->second);
    }
    for(auto it = drop.begin(); it != drop.end(); it++) {
            r.drops.push_back(it->second);
    }
    return r;
}
