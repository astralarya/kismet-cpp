// RollNode.h
// Mara Kim
//
// A node that simulates a dice roll

#ifndef ROLLNODE_H
#define ROLLNODE_H

#include <memory>
#include "Dice.h"

class RollNode {
public:
    struct dice_roll {
        std::string roll;
        std::string report;
        double result;
    };
    typedef std::unique_ptr<RollNode> ptr;
    virtual dice_roll roll() = 0;
    virtual bool multi() = 0;
    virtual ~RollNode();
};

class DiceRollNode: public RollNode {
public:
    typedef std::unique_ptr<DiceRollNode> ptr;
    DiceRollNode();
    DiceRollNode(Dice::roll_type& dice);
    dice_roll roll();
    bool multi();
protected:
    Dice::roll_type _dice;
};

class IntRollNode: public RollNode {
public:
    typedef std::unique_ptr<IntRollNode> ptr;
    IntRollNode(int i);
    dice_roll roll();
    bool multi();
protected:
    int _integer;
};

class MathRollNode: public RollNode {
public:
    typedef std::unique_ptr<MathRollNode> ptr;
    enum mode {ADD,SUB,MULT,DIV};
    MathRollNode(RollNode::ptr& first, RollNode::ptr& second, mode op);
    dice_roll roll();
    bool multi();
protected:
    RollNode::ptr _first, _second;
    mode _operator;
};

class UnaryRollNode: public RollNode {
public:
    typedef std::unique_ptr<UnaryRollNode> ptr;
    typedef MathRollNode::mode mode;
    UnaryRollNode(int i, mode op);
    dice_roll roll();
    bool multi();
protected:
    MathRollNode::ptr _math_node;
};

#endif // ROLLNODE_H
