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

DiceRollNode::DiceRollNode(const unsigned int die):
_dice(die) {
    // ctor
}

DiceRollNode::DiceRollNode():
_dice() {
}

Dice::roll_type& DiceRollNode::getDie() {
    return _dice;
}

const Dice::roll_type& DiceRollNode::getDie() const {
    return _dice;
}

RollNode::ptr DiceRollNode::copy() const {
    return RollNode::ptr(new DiceRollNode(_dice));
}

DiceRollNode::ptr DiceRollNode::copy_typed() const {
    return DiceRollNode::ptr(new DiceRollNode(_dice));
}

RollNode::result_list DiceRollNode::roll() {
    result_list value;
    auto roll = Dice::roll_str(_dice);
    value.push_back(result(roll.report,roll.result));
    return value;
}

std::string DiceRollNode::formula() const {
    std::stringstream ss;
    ss << formula_count() << _dice.die << formula_mod();
    return ss.str();
}

std::string DiceRollNode::formula_count() const {
    std::stringstream ss;
    if(_dice.times > 1)
        ss << _dice.times ;
    ss << 'd';
    return ss.str();
}

std::string DiceRollNode::formula_die() const {
    std::stringstream ss;
    ss << _dice.die;
    return ss.str();
}

std::string DiceRollNode::formula_mod() const {
    std::stringstream ss;
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

ConstRollNode::ConstRollNode(double value):
_atom(value) {
    // ctor
}

ConstRollNode::ConstRollNode(std::string name):
_atom(name) {
    // ctor
}

ConstRollNode::ConstRollNode(std::string name,double value):
_atom(name,value) {
    // ctor
}

ConstRollNode::ConstRollNode(const atom& atom):
_atom(atom) {
    // ctor
}

RollNode::ptr ConstRollNode::copy() const {
    return RollNode::ptr(new ConstRollNode(_atom));
}

RollNode::result_list ConstRollNode::roll() {
    result_list value;
    value.push_back(result(_atom.name,_atom));
    return value;
}

std::string ConstRollNode::formula() const {
    return _atom.name;
}

bool ConstRollNode::multi() const {
    return false;
}

bool ConstRollNode::group() const {
    return false;
}

EnumRollNode::EnumRollNode():
DiceRollNode(),
_enum() {
}

EnumRollNode::EnumRollNode(const atom_list& enumerator, const Dice::roll_type& die):
DiceRollNode(die),
_enum(enumerator) {
}

EnumRollNode::EnumRollNode(const EnumRollNode::enum_roll& roll):
DiceRollNode(roll.die),
_enum(roll.enumerator) {
}

RollNode::ptr EnumRollNode::copy() const {
    return RollNode::ptr(new EnumRollNode(_enum,getDie()));
}

DiceRollNode::ptr EnumRollNode::copy_typed() const {
    return DiceRollNode::ptr(new EnumRollNode(_enum,getDie()));
}

RollNode::result_list EnumRollNode::roll() {
    result_list value;
    getDie().die = _enum.size();
    auto roll = Dice::roll_set(getDie());
    std::stringstream ss;
    atom_list list;
    if(DiceRollNode::multi())
        ss << '{';
    bool first = true;
    for(auto it = roll.rolls.begin(); it != roll.rolls.end(); it++) {
        if(first)
            first = false;
        else
            ss << ',';
        ss << _enum[(*it)-1].name;
        list.push_back(_enum[(*it)-1]);
    }
    if(roll.drops.size())
        ss << " ~ ";
    first = true;
    for(auto it = roll.drops.begin(); it != roll.drops.end(); it++) {
        if(first)
            first = false;
        else
            ss << ',';
        ss << _enum[(*it)-1].name;
    }
    if(DiceRollNode::multi())
        ss << '}';
    value.push_back(result(ss.str(),list));
    return value;
}

std::string EnumRollNode::formula() const {
    std::stringstream ss;
    ss << DiceRollNode::formula_count() << formula_die() << DiceRollNode::formula_mod();
    return ss.str();
}

std::string EnumRollNode::formula_die() const {
    std::stringstream ss;
    ss << '{';
    bool first = true;
    for(auto it = _enum.begin(); it != _enum.end(); it++) {
        if(first)
            first = false;
        else
            ss << ',';
        ss << it->name;
    }
    ss << '}';
    return ss.str();
}

bool EnumRollNode::multi() const {
    return false;
}

bool EnumRollNode::group() const {
    return false;
}

ExprDiceRollNode::ExprDiceRollNode(RollNode::ptr expr):
_expr(std::move(expr)),
_dice() {
}

ExprDiceRollNode::ExprDiceRollNode(RollNode::ptr expr, DiceRollNode::ptr dice):
_expr(std::move(expr)),
_dice(std::move(dice)) {
}

RollNode::ptr ExprDiceRollNode::copy() const {
    return RollNode::ptr(new ExprDiceRollNode(_expr->copy(),_dice->copy_typed()));
}

RollNode::result_list ExprDiceRollNode::roll() {
    result_list value;
    auto expr = _expr->roll();
    for(auto expr_it = expr.begin(); expr_it != expr.end(); expr_it++) {
        result result;
        for(auto expr_result_it = expr_it->value.begin(); expr_result_it != expr_it->value.end(); expr_result_it++) {
            _dice->getDie().times = expr_result_it->value;
            auto roll = _dice->roll();
            std::stringstream ss;
            for(auto roll_it = roll.begin(); roll_it != roll.end(); roll_it++) {
                ss << '{' << expr_it->report;
                std::string value_str(expr_it->value_str());
                if(value_str != expr_it->report)
                    ss << " = " << value_str;
                ss << 'd' << _dice->formula_die() << _dice->formula_mod() << "} " << roll_it->report;
                result.value = roll_it->value;
                result.report = ss.str();
                ss.str("");
            }
        }
        value.push_back(result);
    }
    return value;
}

std::string ExprDiceRollNode::formula() const {
    std::stringstream ss;
    ss << '{' << _expr->formula() << '}' << 'd' << _dice->formula_die() << _dice->formula_mod();
    return ss.str();
}

bool ExprDiceRollNode::multi() const {
    return _dice->multi();
}

bool ExprDiceRollNode::group() const {
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
double MathRollNode::opcalc(double first, double second, mode m) {
    switch(m) {
    case ADD:
        return first + second;
    case SUB:
        return first - second;
    case MULT:
        return first * second;
    case DIV:
        return first / second;
    }
}

RollNode::result_list MathRollNode::roll() {
    RollNode::result_list value;
    std::stringstream ss;
    // roll dice
    auto first = _first->roll();
    for(auto first_it = first.begin(); first_it != first.end(); first_it++) {
        for(auto first_result_it = first_it->value.begin(); first_result_it != first_it->value.end(); first_result_it++) {
            auto second = _second->roll();
            for(auto second_it = second.begin(); second_it != second.end(); second_it++) {
                atom_list list;
                for(auto second_result_it = second_it->value.begin(); second_result_it != second_it->value.end(); second_result_it++) {
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
                    list.push_back(atom(MathRollNode::opcalc(first_result_it->value,second_result_it->value,_operator)));
                }
                value.push_back(result(ss.str(),list));
            }
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
    return true;
}

bool MathRollNode::group() const {
    return false;
}

ParensRollNode::ParensRollNode(RollNode::ptr node):
_node(std::move(node))
{
}

RollNode::ptr ParensRollNode::copy() const {
    return RollNode::ptr(new ParensRollNode(_node->copy()));
}

RollNode::result_list ParensRollNode::roll() {
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

RollNode::result_list MultiRollNode::roll() {
    RollNode::result_list value,
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

RollNode::result_list ListRollNode::roll() {
    RollNode::result_list value,
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

