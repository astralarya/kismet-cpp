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
_root(std::move(root)), _label(label) {
    // ctor
}

Roll::~Roll() {
}

Roll::dice_roll Roll::roll() {
    if(_root)
        _roll = _root->roll();
    return _roll;
}

void Roll::setRoll(RollNode::ptr& root) {
    _root = std::move(root);
}

const Roll::dice_roll& Roll::result() const {
    return _roll;
}

std::string Roll::print() const {
    std::stringstream ss;
    if(_root) {
        if(_label.size())
            ss << _label << ':';
        ss << '[' << _roll.roll  << "] " << _roll.report << " = " << _roll.result;
    }
    return ss.str();
}

void Roll::setLabel(std::string& label) {
    _label = label;
}

const std::string& Roll::label() const {
    return _label;
}
