// Roll.h
// Mara Kim
//
// A tree object that simulates a dice roll

#ifndef ROLL_H
#define ROLL_H

#include "RollNode.h"

class Roll {
public:
    typedef RollNode::result_list dice_roll;

    Roll();
    Roll(RollNode::ptr& root, std::string& label = Options::Instance()->get(Project::DEFAULT_LABEL));
    ~Roll();

    const Roll& operator=(const Roll&);

    dice_roll roll();
    void setRoll(RollNode::ptr& root);
    const dice_roll& result() const;
    std::string print(bool full = false) const;
    void setLabel(std::string& label);
    const std::string& label() const;

private:
    RollNode::ptr _root;
    std::string _label;
    dice_roll _roll;
};

#endif // ROLL_H
