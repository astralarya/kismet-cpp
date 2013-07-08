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
             die_type: Dice::roll_type;
             roll_type: RollNode::ptr;

%left ADD SUB
%left MULT DIV
%left NEWLINE
%token <string> DIE LABEL
%token <integer> COUNT CONSTANT
%type <integer> count constant die
%type <die_type> roll
%type <roll_type> expr headexpr leafexpr
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
    { auto roll = ($1)->roll();
      std::cout << "Roll(" << roll.roll  << "): " << roll.report << " = " << roll.result << std::endl; }
  | label expr
    { auto roll = ($2)->roll();
      std::cout << $1 << '(' << roll.roll  << "): " << roll.report << " = " << roll.result << std::endl; }
  | error NEWLINE
    { std::cout << "error" << std::endl; }
;
label:
    LABEL
    { $$ = d_scanner.matched().substr(0,d_scanner.matched().size()-1); }
;
expr:
    headexpr
    { $$ = std::move($1); }
  | headexpr ADD expr
    { $$ = MathRollNode::ptr(new MathRollNode($1,$3,MathRollNode::ADD)); }
  | headexpr SUB expr
    { $$ = MathRollNode::ptr(new MathRollNode($1,$3,MathRollNode::SUB)); }
  | headexpr MULT expr
    { $$ = MathRollNode::ptr(new MathRollNode($1,$3,MathRollNode::MULT)); }
  | headexpr DIV expr
    { $$ = MathRollNode::ptr(new MathRollNode($1,$3,MathRollNode::DIV)); }
;
headexpr:
    leafexpr
    { $$ = std::move($1); }
  | leafexpr ADD leafexpr
    { $$ = MathRollNode::ptr(new MathRollNode($1,$3,MathRollNode::ADD,true)); }
  | leafexpr SUB leafexpr
    { $$ = MathRollNode::ptr(new MathRollNode($1,$3,MathRollNode::SUB,true)); }
  | leafexpr MULT leafexpr
    { $$ = MathRollNode::ptr(new MathRollNode($1,$3,MathRollNode::MULT,true)); }
  | leafexpr DIV leafexpr
    { $$ = MathRollNode::ptr(new MathRollNode($1,$3,MathRollNode::DIV,true)); }
;
leafexpr:
    roll
    { $$ = DiceRollNode::ptr(new DiceRollNode($1)); }
  | constant
    { $$ = IntRollNode::ptr(new IntRollNode($1)); }
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
