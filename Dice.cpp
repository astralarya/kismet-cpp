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
    // roll dice, recording order
    std::multimap<unsigned int,unsigned int> rolls, // map of results to roll order
                                             keep, // map of roll order to results
                                             drop; // map of roll order to results
    for(int i = 0; i < roll.times; i++)
        rolls.insert(std::pair<unsigned int, unsigned int>(distribution(generator),i));
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
    // construct report
    int result = 0;
    std::stringstream report;
    bool first = true;
    for(auto it = keep.begin(); it != keep.end(); it++) {
            if(first)
                first = false;
            else
                report << " + ";
            result += it->second;
            report << it->second;
    }
    first = true;
    for(auto it = drop.begin(); it != drop.end(); it++) {
            if(first) {
                report << " ~ ";
                first = false;
            } else
                report << ' ';
            report << it->second;
    }
    Dice::result_type r;
    r.result = result;
    r.report = report.str();
    return r;
}
