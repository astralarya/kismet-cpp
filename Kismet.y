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
             roll_type: Dice::roll_type;

%token NEWLINE
%token <string> DIE
%token <integer> CONSTANT
%type <integer> constant count die expr
%type <roll_type> roll

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
    { Dice::result_type result = Dice::roll_str($1);
      $$ = result.first;
      std::cout << "Roll(" << ($1).times << 'd' << ($1).die << "): " << result.second << std::endl; }
  | constant
;
roll:
    count die
    { ($$).times = ($1);
      ($$).die = ($2); }
  | die
    { ($$).times = 1;
      ($$).die = ($1); }
;
count:
    constant
    { $$ = $1; }
;
constant:
    CONSTANT
    { std::stringstream ss;
      ss << d_scanner.matched();
      ss >> $$; }
;
die:
    DIE
    { std::stringstream ss;
      ss << d_scanner.matched().substr(1); 
      ss >> $$; }
;
