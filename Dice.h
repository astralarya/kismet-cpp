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
        result_set():rolls(),drops(){}

        num_vector rolls;
        num_vector drops;
    };
    struct roll_type {
        unsigned times;
        unsigned die;
        unsigned high;
        unsigned low;

        roll_type():
        times(1),
        die(Options::Instance()->get(Project::DEFAULT_DIE)),
        high(0),
        low(0) {}

        roll_type(unsigned int die):
        times(1),
        die(die),
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
