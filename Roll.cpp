// Roll.cpp
// Mara Kim
//
// A tree object that simulates a dice roll

#include "Roll.h"

Roll::Roll():
_root(),
_label() {
    // ctor
}

Roll::Roll(RollNode::ptr& root, std::string& label):
_root(std::move(root)),
_label(label) {
    // ctor
}

Roll::~Roll() {
}

Roll::dice_roll Roll::roll() {
    return _root->roll();
}

void Roll::setRoll(RollNode::ptr& root) {
    _root = std::move(root);
}

void Roll::setLabel(std::string& label) {
    _label = label;
}

const std::string& Roll::label() const {
    return _label;
}
