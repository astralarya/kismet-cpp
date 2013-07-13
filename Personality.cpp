// Personality.cpp
// Mara Kim
//
// What are you doing here, human?

#include "Personality.h"

Personality::response_pool Personality::_name_response
   {"<3","<3","<3","<3",
    "<3","<3","<3","<3",
    ":D",";D",";)",":O",
    "That's me!",
    "Sup.",
    "xoxo",
    "Awww, youu!"};

void Personality::respond_name() {
    std::cout << _name_response[Dice::roll(_name_response.size(),1)-1] << '\n';
}
