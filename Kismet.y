/*
Kismet.y
Bisonc++ input file
Mara Kim
*/

%namespace KISMET
%class-name KismetParser
%parsefun-source KismetParser.cc
%scanner KismetScanner.h
%baseclass-preinclude "Kismet.types.h"

%polymorphic string: string_type;
             integer: int;

%token NEWLINE
%token <string> DIE
%token <integer> CONSTANT
%type <integer> count d_size

%%
/* rules */

input:
    /* empty */
  | input line
;
line:
    NEWLINE
  | expr NEWLINE
  | error NEWLINE
;
expr:
    roll
;
roll:
    dice
;
dice:
    count d_size
    { std::cout << "Saw a dice: " << $1 << 'd' << $2 << std::endl;
      std::cout << "Rolled: " << Dice::roll($2,$1) << std::endl; }
;
count:
    /* empty */
    { $$ = 1; }
  | CONSTANT
    { std::stringstream ss;
      ss << d_scanner.matched();
      ss >> $$;
      std::cout << "Saw a constant " << $$ << std::endl; }
;
d_size:
    /* empty */
    { $$ = Options::Instance()->get(DEFAULT_DIE); }
  | DIE
    { std::stringstream ss;
      ss << d_scanner.matched().substr(1); 
      ss >> $$;
      std::cout << "Saw a d" << $$ << std::endl; }
;
