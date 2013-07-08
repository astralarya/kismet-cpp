// RollNode.cpp
// Mara Kim
//
// A node that simulates a dice roll

#include "RollNode.h"

RollNode::~RollNode() {
    // dtor
}

DiceRollNode::DiceRollNode(Dice::roll_type& dice):
_dice(dice) {
    // ctor
}

RollNode::dice_roll DiceRollNode::roll() {
    RollNode::dice_roll r;
    auto roll = Dice::roll_str(_dice);
    std::stringstream ss;
    ss << _dice.times << 'd' << _dice.die;
    r.roll = ss.str();
    r.report = roll.report;
    r.result = roll.result;
    return r;
}

IntRollNode::IntRollNode(int i):
_integer(i) {
    // ctor
}

RollNode::dice_roll IntRollNode::roll() {
    RollNode::dice_roll r;
    std::stringstream ss;
    ss << _integer;
    r.roll = ss.str();
    r.report = ss.str();
    r.result = _integer;
    return r;
}

MathRollNode::MathRollNode(RollNode::ptr& first, RollNode::ptr& second, MathRollNode::mode op, bool head):
_first(std::move(first)),
_second(std::move(second)),
_operator(op),
_head(head) {
    // ctor
}

RollNode::dice_roll MathRollNode::roll() {
    // roll dice
    auto first = _first->roll();
    auto second = _second->roll();
    RollNode::dice_roll r;
    std::stringstream ss;
    // construct roll
    ss << first.roll;
    switch(_operator) {
    case ADD:
        ss << '+';
        break;
    case SUB:
        ss << '-';
        break;
    case MULT:
        ss << '*';
        break;
    case DIV:
        ss << '/';
        break;
    }
    ss << second.roll;
    r.roll = ss.str();
    // construct report
    ss.str("");
    if(_head)
        ss << '(';
    ss << first.report;
    if(_head)
        ss << ')';
    switch(_operator) {
    case ADD:
        ss << " + ";
        break;
    case SUB:
        ss << " - ";
        break;
    case MULT:
        ss << " * ";
        break;
    case DIV:
        ss << " / ";
        break;
    }
    ss << '(' << second.report << ')';
    r.report = ss.str();
    // set result
    switch(_operator) {
    case ADD:
        r.result = first.result + second.result;
        break;
    case SUB:
        r.result = first.result - second.result;
        break;
    case MULT:
        r.result = first.result * second.result;
        break;
    case DIV:
        r.result = first.result / second.result;
        break;
    }
    return r;
}
