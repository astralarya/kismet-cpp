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
    virtual ~RollNode();
};

class DiceRollNode: public RollNode {
public:
    typedef std::unique_ptr<DiceRollNode> ptr;
    DiceRollNode(Dice::roll_type& dice);
    dice_roll roll();
protected:
    Dice::roll_type _dice;
};

class IntRollNode: public RollNode {
public:
    typedef std::unique_ptr<IntRollNode> ptr;
    IntRollNode(int i);
    dice_roll roll();
protected:
    int _integer;
};

class MathRollNode: public RollNode {
public:
    typedef std::unique_ptr<MathRollNode> ptr;
    enum mode {ADD,SUB,MULT,DIV};
    MathRollNode(RollNode::ptr& first, RollNode::ptr& second, mode op, bool head = false);
    dice_roll roll();
protected:
    RollNode::ptr _first, _second;
    mode _operator;
    bool _head;
};

#endif // ROLLNODE_H
