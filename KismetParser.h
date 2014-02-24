// Kismet parser
// Implemented using boost-spirit

#ifndef KISMETPARSER_H
#define KISMETPARSER_H

#include "Roll.h"
#include "Dice.h"
#include <boost/config/warning_disable.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>

namespace KismetParser {
    bool parse(const std::string&);

    template <typename Iterator>
    struct roll_parser : boost::spirit::qi::grammar<Iterator, Dice::roll_type()> {
        roll_parser() : roll_parser::base_type(start), start(),
        times(), die(), drop_high(), drop_low() {
            using boost::spirit::qi::eps;
            using boost::spirit::qi::lit;
            using boost::spirit::qi::_val;
            using boost::spirit::qi::_1;
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

            start %= times
                    >> die
                    >> drop_high
                    >> drop_low;
        }

        boost::spirit::qi::rule<Iterator, Dice::roll_type()> start;

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
