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

std::string Roll::print(bool full) const {
    std::stringstream ss;
    bool abbrev = false;
    if(_label.size())
        ss << _label << ':';
    if(_root)
        ss << '[' << _root->formula()  << "] ";
    for(auto it = _roll.begin(); it != _roll.end(); it++) {
        if(_roll.size()>1)
            ss << '\n';
        if(!Options::Instance()->get(INTERACTIVE) || it->report.size() < 1000 || full)
            ss << it->report;
        else
            abbrev = true;
        if(_root->multi())
            ss << " = " << it->result;
    }
    if(abbrev) {
        Options::Instance()->set(FULL_REPORT,print(true));
        ss << "\nTAB for report";
    }
    return ss.str();
}

void Roll::setLabel(std::string& label) {
    _label = label;
}

const std::string& Roll::label() const {
    return _label;
}
