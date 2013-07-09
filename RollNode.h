// RollNode.h
// Mara Kim
//
// A node that simulates a dice roll

#ifndef ROLLNODE_H
#define ROLLNODE_H

#include <memory>
#include <vector>
#include "Dice.h"

class RollNode {
public:
    typedef std::vector<Dice::result_type> dice_roll;
    typedef std::unique_ptr<RollNode> ptr;
    virtual dice_roll roll() = 0;
    virtual std::string formula() = 0;
    virtual bool multi() = 0;
    virtual ~RollNode();
};

class DiceRollNode: public RollNode {
public:
    typedef std::unique_ptr<DiceRollNode> ptr;
    DiceRollNode();
    DiceRollNode(Dice::roll_type& dice);
    dice_roll roll();
    std::string formula();
    bool multi();
protected:
    Dice::roll_type _dice;
};

class IntRollNode: public RollNode {
public:
    typedef std::unique_ptr<IntRollNode> ptr;
    IntRollNode(int i);
    dice_roll roll();
    std::string formula();
    bool multi();
protected:
    int _integer;
};

class MathRollNode: public RollNode {
public:
    typedef std::unique_ptr<MathRollNode> ptr;
    enum mode {ADD,SUB,MULT,DIV};
    MathRollNode(RollNode::ptr& first, RollNode::ptr& second, mode op);
    MathRollNode(RollNode* first, RollNode* second, mode op);
    dice_roll roll();
    std::string formula();
    bool multi();
    static char opchar(mode m);
protected:
    RollNode::ptr _first, _second;
    mode _operator;
};

class UnaryRollNode: public RollNode {
public:
    typedef std::unique_ptr<UnaryRollNode> ptr;
    UnaryRollNode(int i, MathRollNode::mode op);
    dice_roll roll();
    std::string formula();
    bool multi();
protected:
    MathRollNode::ptr _math_node;
};

class ParensRollNode: public RollNode {
public:
    typedef std::unique_ptr<ParensRollNode> ptr;
    ParensRollNode(RollNode::ptr& node);
    dice_roll roll();
    std::string formula();
    bool multi();
protected:
    RollNode::ptr _node;
};

class MultiRollNode: public RollNode {
public:
    typedef std::unique_ptr<MultiRollNode> ptr;
    struct modifier {
        RollNode::ptr argument;
        MathRollNode::mode op;
    };
    typedef std::vector<modifier> modifier_list;

    MultiRollNode(RollNode::ptr& dice, modifier_list& mod_list);
    dice_roll roll();
    std::string formula();
    bool multi();
protected:
    RollNode::ptr _node;
    modifier_list _mod_list;
};

#endif // ROLLNODE_H
