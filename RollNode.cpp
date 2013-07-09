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

DiceRollNode::DiceRollNode():
_dice() {
    Dice::roll_type roll;
    roll.times = 1;
    roll.die = Options::Instance()->get(DEFAULT_DIE);
    roll.high = 0;
    roll.low = 0;
    _dice = roll;
}

RollNode::dice_roll DiceRollNode::roll() {
    RollNode::dice_roll r;
    auto roll = Dice::roll_str(_dice);
    std::stringstream ss;
    if(_dice.times > 1)
        ss << _dice.times ;
    ss << 'd' << _dice.die;
    if(_dice.high > 0)
        ss << "-H";
    if(_dice.high > 1)
        ss << _dice.high;
    if(_dice.low > 0)
        ss << "-L";
    if(_dice.low > 1)
        ss << _dice.low;
    r.roll = ss.str();
    r.report = roll.report;
    r.result = roll.result;
    return r;
}

bool DiceRollNode::multi() {
    return _dice.times > 1 || _dice.high > 0 || _dice.low > 0;
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

bool IntRollNode::multi() {
    return false;
}

MathRollNode::MathRollNode(RollNode::ptr& first, RollNode::ptr& second, mode op):
_first(std::move(first)),
_second(std::move(second)),
_operator(op) {
    // ctor
}

MathRollNode::MathRollNode(RollNode* first, RollNode* second, mode op):
_first(first),
_second(second),
_operator(op) {
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
    if(_first->multi())
        ss << '(';
    ss << first.report;
    if(_first->multi())
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
    if(_second->multi())
        ss << '(';
    ss << second.report;
    if(_second->multi())
        ss << ')';
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

bool MathRollNode::multi() {
    return false;
    switch(_operator) {
    case ADD:
    case SUB:
        return true;
    case MULT:
    case DIV:
        return false;
    }
}

UnaryRollNode::UnaryRollNode(int i, MathRollNode::mode op):
_math_node(new MathRollNode(new DiceRollNode(),new IntRollNode(i),op))
{
}

RollNode::dice_roll UnaryRollNode::roll() {
    return _math_node->roll();
}

bool UnaryRollNode::multi() {
    return false;
}

ParensRollNode::ParensRollNode(RollNode::ptr& node):
_node(std::move(node))
{
}

RollNode::dice_roll ParensRollNode::roll() {
    return _node->roll();
}

bool ParensRollNode::multi() {
    return true;
}
