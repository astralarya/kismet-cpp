// Personality.cpp
// Mara Kim
//
// What are you doing here, human?

#include "Personality.h"

Personality::response_pool Personality::_name_response
   {"<3","<3","<3","<3",
    "<3","<3","<3","<3",
    "o/","\\o","\\o/",
    ":D",";D",";)",":O",
    "D:","D':",")':","O:",
    "XD","DX","D'X",">.<",
    "^.^","^.^\"",
    ":P","=)","c:",
    ":/",":|",":\\",
    "/:","|:","\\:",
    ":]","[:","]:",":[",
    ":}","{:","}:",":{",
    "P:",")=",":c",":'c",
    ":3",">:)","O_o","-_-",
    "(:<","O:)","(:O","D:<",
    "T.T",">:D",":x",
    "O_O","O.O","O_o\"","-_-\"",
    "That's me!",
    "Sup.", "Sup?",
    "xoxo",
    "Awww, youu!"};

void Personality::respond_name() {
    std::cout << _name_response[Dice::roll(_name_response.size(),1)-1] << '\n';
}
