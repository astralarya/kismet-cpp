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
    RollNode::dice_roll value;
    auto roll = Dice::roll_str(_dice);
    value.push_back(Dice::result_type(roll.report,roll.result));
    return value;
}

std::string DiceRollNode::formula() {
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
    return ss.str();
}

bool DiceRollNode::multi() {
    return _dice.times > 1 || _dice.high > 0 || _dice.low > 0;
}

IntRollNode::IntRollNode(int i):
_integer(i) {
    // ctor
}

RollNode::dice_roll IntRollNode::roll() {
    RollNode::dice_roll value;
    std::stringstream ss;
    ss << _integer;
    value.push_back(Dice::result_type(ss.str(),_integer));
    return value;
}

std::string IntRollNode::formula() {
    std::stringstream ss;
    ss << _integer;
    return ss.str();
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
    RollNode::dice_roll value;
    std::stringstream ss;
    // roll dice
    auto first = _first->roll();
    for(auto first_it = first.begin(); first_it != first.end(); first_it++) {
        auto second = _second->roll();
        for(auto second_it = second.begin(); second_it != second.end(); second_it++) {
            // construct report
            ss.str("");
            if(_first->multi())
                ss << '(';
            ss << first_it->report;
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
            ss << second_it->report;
            if(_second->multi())
                ss << ')';
            // set result
            double result;
            switch(_operator) {
            case ADD:
                result = first_it->result + second_it->result;
                break;
            case SUB:
                result = first_it->result - second_it->result;
                break;
            case MULT:
                result = first_it->result * second_it->result;
                break;
            case DIV:
                result = first_it->result / second_it->result;
                break;
            }
            value.push_back(Dice::result_type(ss.str(),result));
        }
    }
    return value;
}

std::string MathRollNode::formula() {
    std::stringstream ss;
    // construct roll
    ss << _first->formula();
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
    ss << _second->formula();
    return ss.str();
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

std::string UnaryRollNode::formula() {
    return _math_node->formula();
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

std::string ParensRollNode::formula() {
    return _node->formula();
}
