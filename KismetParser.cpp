// Kismet parser
// Implemented using boost-spirit

#include "KismetParser.h"

bool KismetParser::parse(const std::string& line) {
    Dice::roll_type roll; 
    auto iter = line.begin(),
         end = line.end();
    roll_parser<std::string::const_iterator> parser;
    bool r = parse(iter, end, parser, roll);
    RollNode::ptr node(new DiceRollNode(roll));
    Roll roll_ob(node);
    
    roll_ob.roll();
    std::cout << roll_ob.print() << std::endl;
    return r;
}
