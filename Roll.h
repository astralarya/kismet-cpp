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

    Roll();
    Roll(RollNode::ptr& root, std::string& label = Options::Instance()->get(DEFAULT_LABEL));
    ~Roll();

    dice_roll roll();
    void setRoll(RollNode::ptr& root);
    void setLabel(std::string& label);
    const std::string& label() const;

private:
    RollNode::ptr _root;
    std::string _label;
};

#endif // ROLL_H
