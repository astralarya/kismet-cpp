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
             directive_type: Roll;

%left NEWLINE
%left ADD SUB
%left MULT DIV
%left UNARY
%token <string> DIE LABEL
%token <integer> COUNT CONSTANT
%type <integer> count constant die
%type <string> label
%type <die_type> roll
%type <roll_type> expr leaf factor
%type <directive_type> directive

%%
/* rules */

input:
    /* empty */
  | input line
;
line:
    NEWLINE
    { if(Options::Instance()->get(INTERACTIVE)) std::cout << '>' << std::flush; }
  | directive NEWLINE
    { ($1).roll();
      std::cout << ($1).print() << std::endl;
      if(Options::Instance()->get(INTERACTIVE)) std::cout << '>' << std::flush; }
  | error NEWLINE
    { if(Options::Instance()->get(INTERACTIVE)) std::cout << '>' << std::flush; }
;
directive:
    expr
    { $$ = Roll($1); }
  | label expr
    { $$ = Roll($2,$1); }
  | label
    { $$; }
;
expr:
    factor
    { $$ = std::move($1); }
  | expr ADD expr
    { $$ = MathRollNode::ptr(new MathRollNode($1,$3,MathRollNode::ADD)); }
  | expr SUB expr
    { $$ = MathRollNode::ptr(new MathRollNode($1,$3,MathRollNode::SUB)); }
  | ADD constant %prec UNARY
    { $$ = UnaryRollNode::ptr(new UnaryRollNode($2,MathRollNode::ADD)); }
  | SUB constant %prec UNARY
    { $$ = UnaryRollNode::ptr(new UnaryRollNode($2,MathRollNode::SUB)); }
;
factor:
    leaf
    { $$ = std::move($1); }
  | factor MULT factor
    { $$ = MathRollNode::ptr(new MathRollNode($1,$3,MathRollNode::MULT)); }
  | factor DIV factor
    { $$ = MathRollNode::ptr(new MathRollNode($1,$3,MathRollNode::DIV)); }
;
leaf:
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
label:
    LABEL
    { $$ = d_scanner.matched().substr(0,d_scanner.matched().size()-1); }
;
