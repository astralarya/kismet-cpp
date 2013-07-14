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
        unsigned int result;

        result_type():
        report(),
        result(0) {}
        result_type(std::string report_in,double result_in):
        report(report_in),
        result(result_in) {}
    };
    typedef std::vector<unsigned int> num_vector;
    struct result_set {
        num_vector rolls;
        num_vector drops;
    };
    struct roll_type {
        unsigned int die;
        unsigned int times;
        unsigned int high;
        unsigned int low;

        roll_type():
        die(Options::Instance()->get(DEFAULT_DIE)),
        times(1),
        high(0),
        low(0) {}
        roll_type(unsigned int die):
        die(die),
        times(1),
        high(0),
        low(0) {}
    };

    static int roll(const unsigned int die, const unsigned int times);
    static int roll(const roll_type& roll);
    static result_type roll_str(const unsigned int die, const unsigned int times);
    static result_type roll_str(const roll_type& roll);
    static result_set roll_set(const roll_type& roll);
    // global static random engine
    typedef std::default_random_engine generator;
    static generator& Generator();
private:
    static generator* _Instance;
};

#endif // DICE_H
