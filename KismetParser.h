// Kismet parser
// Implemented using boost-spirit

#ifndef KISMETPARSER_H
#define KISMETPARSER_H

#include "Roll.h"
#include "Dice.h"
#include <boost/spirit/home/qi.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#undef KismetParser
class KismetParser {
public:
    bool parse(const std::string&);

    template <typename Iterator>
    struct roll_parser : boost::spirit::qi::grammar<Iterator, Dice::roll_type()> {
        roll_parser() : roll_parser::base_type(start) {
            using boost::spirit::qi::eps;
            using boost::spirit::qi::uint_;
            using boost::spirit::qi::_val;
            using boost::spirit::qi::_1;

            die = 'd' >> ( uint_
                           | '%'[_val = 100]
                         );

            drop_low %= 'l' >> uint_;

            drop_high %= 'h' >> uint_;

            start %= (uint_ | eps[_val = 1])
                    >> die
                    >> (drop_low | eps[_val=0])
                    >> (drop_high | eps[_val=0]);

        }
        boost::spirit::qi::rule<Iterator, Dice::roll_type()> start;

        boost::spirit::qi::rule<Iterator, unsigned()>
            die,
            drop_low,
            drop_high;
    };
};

BOOST_FUSION_ADAPT_STRUCT(
    Dice::roll_type,
    (unsigned, times)
    (unsigned, die)
    (unsigned, low)
    (unsigned, high)
)


#endif // KISMETPARSER_H
