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

%polymorphic string: std::string;
             integer: int;
             roll_type: Dice::roll_type;

%token NEWLINE
%token <string> DIE LABEL
%token <integer> CONSTANT
%type <integer> constant die expr
%type <roll_type> roll
%type <string> label

%%
/* rules */

input:
    /* empty */
  | input line
;
line:
    NEWLINE
  | directive
  | error NEWLINE
;
directive:
    label NEWLINE
  | expr NEWLINE
  | label expr NEWLINE
;
label:
    LABEL
    { $$ = d_scanner.matched().substr(0,d_scanner.matched().size()-1); 
      std::cout << "Saw a label: " << $$ << std::endl; }
;
expr:
    roll
    { Dice::result_type result = Dice::roll_str($1);
      $$ = result.first;
      std::cout << "Roll(" << ($1).times << 'd' << ($1).die << "): " << result.second << std::endl; }
  | constant
    { $$ = $1;
      std::cout << "Constant: " << $1 << std::endl; }
;
roll:
    constant die
    { ($$).times = $1;
      ($$).die = $2; }
  | die
    { ($$).times = 1;
      ($$).die = $1; }
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
