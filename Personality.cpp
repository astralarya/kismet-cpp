// Personality.cpp
// Mara Kim
//
// What are you doing here, human?

#include "Personality.h"

Personality::response_pool Personality::_name_response
   {"<3","<3","<3","<3","<3","<3","<3","<3","<3","<3","<3","<3",
    "o/","\\o","\\o/",":D",";D",";)",":O",
    "D:","D':",")':","O:","XD","DX","D'X",">.<",
    ":P","=)","(=","c:",":/",":|",":\\","/:","|:","\\:",
    ":]","[:","]:",":[",";]","[;",">:/",">:\\","/:<","\\:<",
    ":}","{:","}:",":{","P:",")=",":c",":'c","p:",":p","d:",":b",
    ":3",">:)","O_o","o_O","-_-","O_O","O.O","o_O\"","O_o;","-_-\"",
    ":-O","°o°","°O°","X-P","XP","ಠ_ಠ","</3","(~_~)","(^^;)","(';')",
    "^.^","^.^\"","^_^","^_^\"","(>_<)","(>_<)>","(゜_゜)",
    "(^。^)","(*^_^*)","(-_-)zzz","(^_-)","_(._.)_","\\(^o^)/",
    "(@_@)","(+_+)","(*_*)","!(^^)!","(p_-)","(╯°□°）╯︵ ┻━┻",
    "(:<","O:)","(:O","D:<","T.T",">:D",":x",":^)","B^D","8D",
    "!!!","???","!?!","?!?","!!","??","?!","!?","...","..?","..!","...?","...!",
    "That's me!", "How's it going?","Love you too!!", "Love you too!","Awww, youu!", "Ahhh!!",
    "hello", "Hello?", "Hello!","What's up?", "Yes?","Yes!", "YES!", "No.", "No!", "NO!",
    "What?", "Why?", "wut", "wut?", "err", "Why??", "What??", "What!?",
     "Sup.", "Sup?", "*sigh*", "*clap clap*", "hum", "hmmm", "uhh", "umm", "wtf", "wtf!", "wtf?",
    "xoxo", "asdf", "ababa", "42","Kismet","kismet", "KISMET", "KISMET!!", "0xkismet"
    };

void Personality::respond_name() {
    std::cout << _name_response[Dice::roll(_name_response.size(),1)-1] << '\n';
}
