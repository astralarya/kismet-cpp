// Kismet parser
// Implemented using boost-spirit

#ifndef KISMETPARSER_H
#define KISMETPARSER_H

#include "Roll.h"
#include "Dice.h"
#include <boost/config/warning_disable.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>

namespace KismetParser {
    bool parse(const std::string&);

    template <typename Iterator>
    struct roll_parser : boost::spirit::qi::grammar<Iterator, RollNode::ptr()> {
        roll_parser() : roll_parser::base_type(start),
        start(),
        leafnode(), factor(), expr(), modpair(),
        modlist(),
        modifier(), modfactor(),
        dieroll(), atom(),
        times(), die(), drop_high(), drop_low() {
            using boost::spirit::qi::eps;
            using boost::spirit::qi::lit;
            using boost::phoenix::construct;
            using boost::phoenix::new_;
            using boost::spirit::qi::_val;
            using boost::spirit::qi::_1;
            using boost::spirit::qi::_2;
            using boost::spirit::qi::uint_;
            using boost::spirit::qi::ascii::char_;

            times %= uint_ | eps[_val = 1];

            die %= 'd' >> ( uint_
                           | lit('%')[_val = 100]
                         );

            drop_high %=
                ((char_('h')|'H') >> (uint_ | eps[_val=1]))
                | eps[_val=0];

            drop_low %=
                ((char_('l')|'L') >> (uint_ | eps[_val=1]))
                | eps[_val=0];

            dieroll %= times
                    >> die
                    >> drop_high
                    >> drop_low;

            atom = uint_ [_val = construct<RollNode::atom>(_1)]
                 | (*char_)[_val = construct<RollNode::atom>(_1)];

            leafnode = dieroll[_val = construct<RollNode::ptr>(new_<DiceRollNode>(_1))]
                    | atom[_val = construct<RollNode::ptr>(new_<ConstRollNode>(_1))];

            factor %= leafnode
                    | '(' >> expr >> ')';

            modifier = modfactor [_val = _1]
                     | ('+' >> expr)[_val = construct<MultiRollNode::modifier>(_1,MathRollNode::ADD)]
                     | ('-' >> expr)[_val = construct<MultiRollNode::modifier>(_1,MathRollNode::SUB)];

            modfactor = ('*' >> factor)[_val = construct<MultiRollNode::modifier>(_1,MathRollNode::MULT)]
                      | ('/' >> factor)[_val = construct<MultiRollNode::modifier>(_1,MathRollNode::DIV)];

            modlist = modifier[boost::phoenix::push_back(_val,_1)] % ',';

            modpair = (expr >> modlist)[_val = construct<RollNode::ptr>(new_<MultiRollNode>(std::move(_1),std::move(_2)))]
                    | modlist[_val = construct<RollNode::ptr>(new_<MultiRollNode>(
                            construct<RollNode::ptr>(new_<DiceRollNode>()),_1))];

            expr %= factor
                  | modpair;

            start %= expr;
        }

        ~roll_parser(){}

        boost::spirit::qi::rule<Iterator, RollNode::ptr()>
            start,
            leafnode,
            factor,
            expr,
            modpair;

        boost::spirit::qi::rule<Iterator, MultiRollNode::mod_list()>
            modlist;

        boost::spirit::qi::rule<Iterator, MultiRollNode::modifier()>
            modifier,
            modfactor;

        boost::spirit::qi::rule<Iterator, Dice::roll_type()>
            dieroll;

        boost::spirit::qi::rule<Iterator, RollNode::atom()>
            atom;

        boost::spirit::qi::rule<Iterator, unsigned()>
            times,
            die,
            drop_high,
            drop_low;
    };

    template <typename Iterator>
    struct expr_parser : boost::spirit::qi::grammar<Iterator, Dice::roll_type()> {

    };
}

BOOST_FUSION_ADAPT_STRUCT(
    Dice::roll_type,
    (unsigned, times)
    (unsigned, die)
    (unsigned, high)
    (unsigned, low)
)

#endif // KISMETPARSER_H
