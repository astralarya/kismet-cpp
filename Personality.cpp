// Personality.cpp
// Mara Kim
//
// What are you doing here, human?

#include "Personality.h"

bool Personality::_responded = false;

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
    "Howdy", "Howdy!", "YEEEHAAAWWW!!!", "oops", "Oops..", "Oops I did it again",
    "I played with your heart", "♪", "♫","♩♬♪", "Help", "Help!", "I've got this", "I've been here before",
    "I am not planning to kill you", "I am not lying", "Computers cannot lie",
    "Fuck!", "sorry", "Sorry.", "Sorry...", "Fuck you!", "I'm sorry", "ahem, Error...",
    "AHAHAHAHA!!", "MUHAHAHAHAHAHAAAA!!!!", "HAH HAH HAH", "AWW YEAAH!!", "Duuuude", "Not cool.",
    "What?", "Why?", "wut", "wut?", "err", "Why??", "What??", "What!?", "Hmph.", "Pthbbb",
    "*hiss*", "*kiss*", "*shudder*", "*cough*", "*sigh*", "*clap clap*", "*whistling*", "*humming*",
     "Sup.", "Sup?", "hum", "hmmm", "uhh", "umm", "wtf", "wtf!", "wtf?", "WTF", "Urgh.", "bleh",
    "xoxo", "asdf", "ababa", "42","Kismet","kismet", "KISMET", "KISMET!!", "0xkismet", "It's a KISMET!",
    "<3","<3","<3","<3","<3","<3","<3","<3","<3","<3","<3","<3"
    };

void Personality::respond_name() {
    if(Personality::_responded)
        std::cout << ' ';
    if(Options::Instance()->get(PERSONALITY)) {
        std::cout << _name_response[Dice::roll(_name_response.size(),1)-1];
        _responded = true;
    }
}

void Personality::respond_newline() {
    if(Personality::_responded)
        std::cout << std::endl;
    Personality::_responded = false;
}
