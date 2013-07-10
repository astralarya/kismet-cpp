// RollNode.cpp
// Mara Kim
//
// A node that simulates a dice roll

#include "RollNode.h"

RollNode::~RollNode() {
    // dtor
}

DiceRollNode::DiceRollNode(const Dice::roll_type& dice):
_dice(dice) {
    // ctor
}

DiceRollNode::DiceRollNode():
_dice() {
}

RollNode::ptr DiceRollNode::copy() const {
    return RollNode::ptr(new DiceRollNode(_dice));
}

RollNode::dice_roll DiceRollNode::roll() {
    RollNode::dice_roll value;
    auto roll = Dice::roll_str(_dice);
    value.push_back(Dice::result_type(roll.report,roll.result));
    return value;
}

std::string DiceRollNode::formula() const {
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

bool DiceRollNode::multi() const {
    return _dice.times > 1 || _dice.high > 0 || _dice.low > 0;
}

bool DiceRollNode::group() const {
    return false;
}

bool DiceRollNode::leaf() const {
    return true;
}

IntRollNode::IntRollNode(int i):
_integer(i) {
    // ctor
}

RollNode::ptr IntRollNode::copy() const {
    return RollNode::ptr(new IntRollNode(_integer));
}

RollNode::dice_roll IntRollNode::roll() {
    RollNode::dice_roll value;
    std::stringstream ss;
    ss << _integer;
    value.push_back(Dice::result_type(ss.str(),_integer));
    return value;
}

std::string IntRollNode::formula() const {
    std::stringstream ss;
    ss << _integer;
    return ss.str();
}

bool IntRollNode::multi() const {
    return false;
}

bool IntRollNode::group() const {
    return false;
}

bool IntRollNode::leaf() const {
    return true;
}

ExprDiceRollNode::ExprDiceRollNode(RollNode::ptr expr):
_expr(std::move(expr)),
_dice() {
}

ExprDiceRollNode::ExprDiceRollNode(RollNode::ptr expr, const Dice::roll_type& dice):
_expr(std::move(expr)),
_dice(dice) {
}

RollNode::ptr ExprDiceRollNode::copy() const {
    return RollNode::ptr(new ExprDiceRollNode(_expr->copy(),_dice));
}

RollNode::dice_roll ExprDiceRollNode::roll() {
    RollNode::dice_roll value;
    auto expr = _expr->roll();
    for(auto expr_it = expr.begin(); expr_it != expr.end(); expr_it++) {
        _dice.times = expr_it->result;
        DiceRollNode d(_dice);
        auto roll = d.roll();
        std::stringstream ss;
        for(auto roll_it = roll.begin(); roll_it != roll.end(); roll_it++) {
            ss << '{' << d.formula() << "} " << roll_it->report;
            value.push_back(Dice::result_type(ss.str(),roll_it->result));
            ss.str("");
        }
    }
    return value;
}

std::string ExprDiceRollNode::formula() const {
    std::stringstream ss;
    ss << '{' << _expr->formula() << '}' << 'd' << _dice.die;
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

bool ExprDiceRollNode::multi() const {
    return true;
}

bool ExprDiceRollNode::group() const {
    return false;
}

bool ExprDiceRollNode::leaf() const {
    return false;
}

MathRollNode::MathRollNode(RollNode::ptr first, RollNode::ptr second, const mode op):
_first(std::move(first)),
_second(std::move(second)),
_operator(op) {
    // ctor
}

MathRollNode::MathRollNode(RollNode* first, RollNode* second, const mode op):
_first(first),
_second(second),
_operator(op) {
    // ctor
}

RollNode::ptr MathRollNode::copy() const {
    return RollNode::ptr(new MathRollNode(_first->copy(),_second->copy(),_operator));
}

char MathRollNode::opchar(mode m) {
    switch(m) {
    case ADD:
        return '+';
    case SUB:
        return '-';
    case MULT:
        return '*';
    case DIV:
        return '/';
    }
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
            ss << ' ' << MathRollNode::opchar(_operator) << ' ';
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

std::string MathRollNode::formula() const {
    std::stringstream ss;
    // construct roll
    if(_first->group())
        ss << '(';
    ss << _first->formula();
    if(_first->group())
        ss << ')';
    ss << MathRollNode::opchar(_operator);
    if(_second->group())
        ss << '(';
    ss << _second->formula();
    if(_second->group())
        ss << ')';
    return ss.str();
}

bool MathRollNode::multi() const {
    return false;
}

bool MathRollNode::group() const {
    return false;
}

bool MathRollNode::leaf() const {
    return false;
}

ParensRollNode::ParensRollNode(RollNode::ptr node):
_node(std::move(node))
{
}

RollNode::ptr ParensRollNode::copy() const {
    return RollNode::ptr(new ParensRollNode(_node->copy()));
}

RollNode::dice_roll ParensRollNode::roll() {
    return _node->roll();
}

std::string ParensRollNode::formula() const {
    return _node->formula();
}

bool ParensRollNode::multi() const {
    return true;
}

bool ParensRollNode::group() const {
    return true;
}

bool ParensRollNode::leaf() const {
    return false;
}

MultiRollNode::MultiRollNode(RollNode::ptr node, MultiRollNode::mod_list mod_list):
_node(std::move(node)),
_mod_list(std::move(mod_list)),
_node_list() {
    for(auto it = _mod_list.begin(); it != _mod_list.end(); it++)
        _node_list.emplace_back(RollNode::ptr(new MathRollNode(_node->copy(),it->argument->copy(),it->op)));
}

RollNode::ptr MultiRollNode::copy() const {
    return RollNode::ptr(new MultiRollNode(_node->copy(),MultiRollNode::copy_modlist(_mod_list)));
}

MultiRollNode::mod_list MultiRollNode::copy_modlist(const mod_list& inlist) {
    mod_list list;
    for(auto it = inlist.begin(); it != inlist.end(); it++) {
        modifier m;
        m.op = it->op;
        m.argument = it->argument->copy();
        list.emplace_back(std::move(m));
    }
    return list;
}

RollNode::dice_roll MultiRollNode::roll() {
    RollNode::dice_roll value,
                        itr_value;
    for(auto it = _node_list.begin(); it != _node_list.end(); it++) {
        itr_value = (*it)->roll();
        value.insert(value.end(),itr_value.begin(),itr_value.end());
    }
    return value;
}

std::string MultiRollNode::formula() const {
    std::stringstream ss;
    if(_node->group())
        ss << '(';
    ss << _node->formula();
    if(_node->group())
        ss << ')';
    bool first = true;
    for(auto it = _mod_list.begin(); it != _mod_list.end(); it++) {
        if(first)
            first = false;
        else
            ss << ',';
        ss << MathRollNode::opchar(it->op);
        if(it->argument->group())
            ss << '(';
        ss << it->argument->formula();
        if(it->argument->group())
            ss << ')';
    }
    return ss.str();
}

bool MultiRollNode::multi() const {
    return _mod_list.size() > 1;
}

bool MultiRollNode::group() const {
    return _mod_list.size() > 1;
}

bool MultiRollNode::leaf() const {
    return false;
}

ListRollNode::ListRollNode():
_node_list()
{
}

ListRollNode::ListRollNode(ListRollNode::node_list list):
_node_list(std::move(list))
{
}

RollNode::ptr ListRollNode::copy() const {
    return RollNode::ptr(new ListRollNode(ListRollNode::copy_nodelist(_node_list)));
}

ListRollNode::node_list ListRollNode::copy_nodelist(const node_list& inlist) {
    node_list list;
    for(auto it = inlist.begin(); it != inlist.end(); it++) {
        list.emplace_back((*it)->copy());
    }
    return list;
}

void ListRollNode::insert(RollNode::ptr node) {
    _node_list.emplace_back(std::move(node));
}

RollNode::dice_roll ListRollNode::roll() {
    RollNode::dice_roll value,
                        itr_value;
    for(auto it = _node_list.begin(); it != _node_list.end(); it++) {
        itr_value = (*it)->roll();
        value.insert(value.end(),itr_value.begin(),itr_value.end());
    }
    return value;
}

std::string ListRollNode::formula() const {
    std::stringstream ss;
    bool first = true;
    for(auto it = _node_list.begin(); it != _node_list.end(); it++) {
        if(first)
            first = false;
        else
            ss << ',';
        if((*it)->group())
            ss << '(';
        ss << (*it)->formula();
        if((*it)->group())
            ss << ')';
    }
    return ss.str();
}

bool ListRollNode::multi() const {
    return _node_list.size() > 1;
}

bool ListRollNode::group() const {
    return _node_list.size() > 1;
}

bool ListRollNode::leaf() const {
    return false;
}
