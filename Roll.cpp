// Roll.cpp
// Mara Kim
//
// A tree object that simulates a dice roll

#include "Roll.h"

Roll::Roll(RollNode::ptr& root):
_root(std::move(root))
{
    // ctor
}

Roll::~Roll() {
}

Roll::dice_roll Roll::roll() {
    return _root->roll();
}
