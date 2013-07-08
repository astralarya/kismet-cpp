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
             result_type: Dice::dice_roll;

%left PLUS MINUS
%left NEWLINE
%token <string> DIE LABEL
%token <integer> COUNT CONSTANT
%type <integer> count constant die
%type <roll_type> roll
%type <result_type> expr
%type <string> label

%%
/* rules */

input:
    /* empty */
  | input line
;
line:
    NEWLINE
  | expr
    { std::cout << "Roll(" << ($1).roll  << "): " << ($1).report << " = " << ($1).result << std::endl; }
  | label expr
    { std::cout << $1 << '(' << ($2).roll  << "): " << ($2).report << " = " << ($2).result << std::endl; }
  | error NEWLINE
    { std::cout << "error" << std::endl; }
;
label:
    LABEL
    { $$ = d_scanner.matched().substr(0,d_scanner.matched().size()-1); }
;
expr:
    roll
    { Dice::result_type result = Dice::roll_str($1);
      std::stringstream ss;
      ss << ($1).times << 'd' << ($1).die;
      ($$).roll = ss.str();
      ($$).report = result.report;
      ($$).result = result.result; }
  | constant
    { std::stringstream ss;
      ss << $1;
      ($$).roll = ss.str();
      ($$).report = ss.str();
      ($$).result = $1;
      std::cout << "Constant: " << $1 << std::endl; }
  | expr PLUS expr
    { std::stringstream ss;
      ss << ($1).roll << '+' << ($3).roll;
      ($$).roll = ss.str();
      ss.str("");
      ss << ($1).report << " + " << ($3).report;
      ($$).report = ss.str();
      ($$).result = ($1).result + ($3).result; }
  | expr MINUS expr
    { std::stringstream ss;
      ss << ($1).roll << '-' << ($3).roll;
      ($$).roll = ss.str();
      ss.str("");
      ss << ($1).report << " - " << ($3).report;
      ($$).report = ss.str();
      ($$).result = ($1).result - ($3).result; }
;
roll:
    count die
    { ($$).times = $1;
      ($$).die = $2; }
  | die
    { ($$).times = 1;
      ($$).die = $1; }
;
count:
    COUNT
    { std::stringstream ss;
      ss << d_scanner.matched();
      ss >> $$; }
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
