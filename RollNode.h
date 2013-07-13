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
    typedef std::vector<Dice::result_set> roll_set;
    typedef std::unique_ptr<RollNode> ptr;
    virtual ptr copy() const = 0;
    virtual dice_roll roll() = 0;
    virtual std::string formula() const = 0;
    virtual bool multi() const = 0;
    virtual bool group() const = 0;
    virtual bool leaf() const = 0;
    virtual ~RollNode();
};



class DiceRollNode: public RollNode {
public:
    typedef std::unique_ptr<DiceRollNode> ptr;
    DiceRollNode();
    DiceRollNode(const Dice::roll_type& dice);
    DiceRollNode(const unsigned int die);
    Dice::roll_type& getDie();
    const Dice::roll_type& getDie() const;
    virtual RollNode::ptr copy() const;
    virtual DiceRollNode::ptr copy_typed() const;
    virtual dice_roll roll();
    roll_set roll_set();
    virtual std::string formula() const;
    std::string formula_count() const;
    virtual std::string formula_die() const;
    std::string formula_mod() const;
    virtual bool multi() const;
    virtual bool group() const;
    virtual bool leaf() const;
protected:
    Dice::roll_type _dice;
};

class IntRollNode: public RollNode {
public:
    typedef std::unique_ptr<IntRollNode> ptr;
    IntRollNode(int i);
    RollNode::ptr copy() const;
    dice_roll roll();
    std::string formula() const;
    bool multi() const;
    bool group() const;
    bool leaf() const;
protected:
    int _integer;
};

class EnumRollNode: public DiceRollNode {
public:
    typedef std::vector<std::string> enum_type;
    typedef std::map<std::string,unsigned int> result_map;
    struct result_set {
        std::string report;
        enum_type result;

        result_set(std::string report,enum_type result):
        report(report),
        result(result) {}
    };
    struct enum_roll {
        enum_type enumerator;
        Dice::roll_type die;
    };
    typedef std::vector<result_set> dice_roll_set;

    EnumRollNode();
    EnumRollNode(const enum_type& enumerator, Dice::roll_type die);
    EnumRollNode(const enum_roll& roll);
    RollNode::ptr copy() const;
    DiceRollNode::ptr copy_typed() const;
    dice_roll roll();
    dice_roll_set roll_enum();
    std::string formula() const;
    std::string formula_count() const;
    std::string formula_die() const;
    std::string formula_mod() const;
    bool multi() const;
    bool group() const;
    bool leaf() const;
protected:
    enum_type _enum;
};

class ExprDiceRollNode: public RollNode {
public:
    typedef std::unique_ptr<ExprDiceRollNode> ptr;
    ExprDiceRollNode(RollNode::ptr expr);
    ExprDiceRollNode(RollNode::ptr expr, DiceRollNode::ptr dice);
    RollNode::ptr copy() const;
    dice_roll roll();
    std::string formula() const;
    bool multi() const;
    bool group() const;
    bool leaf() const;
protected:
    RollNode::ptr _expr;
    DiceRollNode::ptr _dice;
};

class MathRollNode: public RollNode {
public:
    typedef std::unique_ptr<MathRollNode> ptr;
    enum mode {ADD,SUB,MULT,DIV};
    MathRollNode(RollNode::ptr first, RollNode::ptr second, const mode op);
    MathRollNode(RollNode* first, RollNode* second, const mode op);
    RollNode::ptr copy() const;
    static char opchar(mode m);
    dice_roll roll();
    std::string formula() const;
    bool multi() const;
    bool group() const;
    bool leaf() const;
protected:
    RollNode::ptr _first, _second;
    mode _operator;
};

class ParensRollNode: public RollNode {
public:
    typedef std::unique_ptr<ParensRollNode> ptr;
    ParensRollNode(RollNode::ptr node);
    RollNode::ptr copy() const;
    dice_roll roll();
    std::string formula() const;
    bool multi() const;
    bool group() const;
    bool leaf() const;
protected:
    RollNode::ptr _node;
};

class MultiRollNode: public RollNode {
public:
    typedef std::unique_ptr<MultiRollNode> ptr;
    struct modifier {
        RollNode::ptr argument;
        MathRollNode::mode op;

        void setArgument(RollNode::ptr argument_in) {
            argument = std::move(argument_in);
        }
    };
    typedef std::vector<modifier> mod_list;
    typedef std::vector<RollNode::ptr> node_list;

    MultiRollNode(RollNode::ptr node, mod_list mod_list);
    RollNode::ptr copy() const;
    static mod_list copy_modlist(const mod_list& m);
    dice_roll roll();
    std::string formula() const;
    bool multi() const;
    bool group() const;
    bool leaf() const;
protected:
    RollNode::ptr _node;

    mod_list _mod_list;
    node_list _node_list;
};

class ListRollNode: public RollNode {
public:
    typedef std::unique_ptr<ListRollNode> ptr;
    typedef std::vector<RollNode::ptr> node_list;

    ListRollNode();
    ListRollNode(node_list list);
    RollNode::ptr copy() const;
    static node_list copy_nodelist(const node_list& m);
    void insert(RollNode::ptr node);
    dice_roll roll();
    std::string formula() const;
    bool multi() const;
    bool group() const;
    bool leaf() const;
protected:
    node_list _node_list;
};

#endif // ROLLNODE_H
