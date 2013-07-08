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
%type <integer> d_size

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
;
count:
    /* empty */
  | CONSTANT
;
d_size:
    DIE
  { std::stringstream ss;
    ss << d_scanner.matched().substr(1); 
    ss >> $$;
    std::cout << "Saw a d" << $$ << std::endl; }
;
