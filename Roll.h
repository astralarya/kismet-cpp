// Roll.h
// Mara Kim
//
// A tree object that simulates a dice roll

#ifndef ROLL_H
#define ROLL_H

#include "RollNode.h"

class Roll {
public:
    typedef RollNode::dice_roll dice_roll;

    Roll(RollNode::ptr& root);
    ~Roll();

    dice_roll roll();

private:
    RollNode::ptr _root;
};

#endif // ROLL_H
