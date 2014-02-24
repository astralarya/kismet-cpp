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
    /// TYPES ///
    typedef std::shared_ptr<RollNode> ptr;
    struct atom {
        // Variables
        std::string name;
        double value;
        bool null;
        // Functions
        atom(std::string name,double value):
        name(name),value(value),null(false) {}
        atom(double value):
        name(),value(value),null(false) {
            std::stringstream ss;
            ss << value;
            name = ss.str();
        }
        atom(std::string name):
        name(name),value(0),null(true) {}
        atom():
        name(),value(0),null(true) {}
    };
    typedef std::vector<atom> atom_list;
    struct result {
         // Variables
         std::string report;
         atom_list value;
         // Functions
         result(std::string report,atom_list value):
         report(report), value(value) {}
         result(std::string report,atom value):
         report(report), value(1,value) {}
         result():
         report(),value() {}

         std::string value_str() const {
             std::map<std::string,unsigned int> map;
             std::stringstream ss;
             // Build value
             if(value.size() > 1)
                 ss << '{';
             bool first = true;
             for(auto it = value.begin(); it != value.end(); it++) {
                 if(first)
                     first = false;
                 else
                     ss << ',';
                 ss << it->name;
                 auto find = map.find(it->name);
                 if(find != map.end())
                     find->second++;
                 else
                     map[it->name] = 1;
             }
             if(value.size() > 1)
                 ss << '}';
             std::string value_str(ss.str());

             // Build result
             ss.str("");
             if(value.size() > 1)
                 ss << '{';
             first = true;
             for(auto it = map.begin(); it != map.end(); it++) {
                 if(first)
                     first = false;
                 else
                     ss << ',';
                 ss << it->first;
                 if(it->second > 1)
                     ss << '*' << it->second;
             }
             if(value.size() > 1)
                 ss << '}';
             std::string summary_str(ss.str());
             
             ss.str("");
             if(value_str != report)
                 if(summary_str != value_str)
                     ss << value_str << " = " << summary_str;
                 else
                     ss << value_str;
             else
                 ss << summary_str;
             
             return ss.str();
         }
    };
    typedef std::vector<result> result_list;

    /// FUNCTIONS///
    virtual ptr copy() const = 0;
    virtual result_list roll() = 0;
    virtual std::string formula() const = 0;
    virtual bool multi() const = 0;
    virtual bool group() const = 0;
    virtual ~RollNode();
};

class DiceRollNode: public RollNode {
public:
    typedef std::shared_ptr<DiceRollNode> ptr;
    typedef std::vector<Dice::result_set> result_set;
    DiceRollNode();
    DiceRollNode(const Dice::roll_type& dice);
    DiceRollNode(const unsigned die);
    Dice::roll_type& getDie();
    const Dice::roll_type& getDie() const;
    virtual RollNode::ptr copy() const;
    virtual DiceRollNode::ptr copy_typed() const;
    virtual result_list roll();
    result_set roll_set();

    virtual std::string formula() const;
    std::string formula_count() const;
    virtual std::string formula_die() const;
    std::string formula_mod() const;

    virtual bool multi() const;
    virtual bool group() const;
protected:
    Dice::roll_type _dice;
};

class ConstRollNode: public RollNode {
public:
    typedef std::shared_ptr<ConstRollNode> ptr;
    ConstRollNode(double value);
    ConstRollNode(std::string name);
    ConstRollNode(std::string name,double value);
    ConstRollNode(const atom& atom);
    RollNode::ptr copy() const;
    result_list roll();
    std::string formula() const;
    bool multi() const;
    bool group() const;
protected:
    atom _atom;
};

class EnumRollNode: public DiceRollNode {
public:
    struct enum_roll {
        atom_list enumerator;
        Dice::roll_type die;
    };

    EnumRollNode();
    EnumRollNode(const atom_list& enumerator, const Dice::roll_type& die);
    EnumRollNode(const enum_roll& roll);
    RollNode::ptr copy() const;
    DiceRollNode::ptr copy_typed() const;
    result_list roll();
    std::string formula() const;
    std::string formula_count() const;
    std::string formula_die() const;
    std::string formula_mod() const;
    bool multi() const;
    bool group() const;
protected:
    atom_list _enum;
};

class ExprDiceRollNode: public RollNode {
public:
    typedef std::shared_ptr<ExprDiceRollNode> ptr;
    ExprDiceRollNode(RollNode::ptr expr);
    ExprDiceRollNode(RollNode::ptr expr, DiceRollNode::ptr dice);
    RollNode::ptr copy() const;
    result_list roll();
    std::string formula() const;
    bool multi() const;
    bool group() const;
protected:
    RollNode::ptr _expr;
    DiceRollNode::ptr _dice;
};

class MathRollNode: public RollNode {
public:
    typedef std::shared_ptr<MathRollNode> ptr;
    enum mode {ADD,SUB,MULT,DIV};
    MathRollNode(RollNode::ptr first, RollNode::ptr second, const mode op);
    MathRollNode(RollNode* first, RollNode* second, const mode op);
    RollNode::ptr copy() const;
    static char opchar(mode m);
    static double opcalc(double first, double second, mode m);
    result_list roll();
    std::string formula() const;
    bool multi() const;
    bool group() const;
protected:
    RollNode::ptr _first, _second;
    mode _operator;
};

class ParensRollNode: public RollNode {
public:
    typedef std::shared_ptr<ParensRollNode> ptr;
    ParensRollNode(RollNode::ptr node);
    RollNode::ptr copy() const;
    result_list roll();
    std::string formula() const;
    bool multi() const;
    bool group() const;
protected:
    RollNode::ptr _node;
};

class MultiRollNode: public RollNode {
public:
    typedef std::shared_ptr<MultiRollNode> ptr;
    struct modifier {
        modifier():argument(),op(){}

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
    result_list roll();
    std::string formula() const;
    bool multi() const;
    bool group() const;
protected:
    RollNode::ptr _node;

    mod_list _mod_list;
    node_list _node_list;
};

class ListRollNode: public RollNode {
public:
    typedef std::shared_ptr<ListRollNode> ptr;
    typedef std::vector<RollNode::ptr> node_list;

    ListRollNode();
    ListRollNode(node_list list);
    RollNode::ptr copy() const;
    static node_list copy_nodelist(const node_list& m);
    void insert(RollNode::ptr node);
    result_list roll();
    std::string formula() const;
    bool multi() const;
    bool group() const;
protected:
    node_list _node_list;
};

#endif // ROLLNODE_H
