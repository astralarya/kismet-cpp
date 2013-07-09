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

%left NEWLINE
%left ADD SUB
%left MULT DIV
%left UNARY
%token <string> DIE LABEL
%token <integer> COUNT CONSTANT
%type <integer> count constant die
%type <die_type> roll
%type <roll_type> expr leaf factor
%type <string> label

%%
/* rules */

input:
    /* empty */
  | input line
;
line:
    NEWLINE
    { if(Options::Instance()->get(INTERACTIVE)) std::cout << '>' << std::flush; }
  | expr
    { auto roll = ($1)->roll();
      std::cout << "Expr(" << roll.roll  << "): " << roll.report << " = " << roll.result << std::endl; }
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
    factor
    { $$ = std::move($1); }
  | expr ADD expr
    { $$ = MathRollNode::ptr(new MathRollNode($1,$3,MathRollNode::ADD)); }
  | expr SUB expr
    { $$ = MathRollNode::ptr(new MathRollNode($1,$3,MathRollNode::SUB)); }
  | ADD constant %prec UNARY
    { $$ = UnaryRollNode::ptr(new UnaryRollNode($2,MathRollNode::ADD)); }
/*
  | SUB constant %prec UNARY
    { Dice::roll_type roll;
      roll.times = 1;
      roll.die = Options::Instance()->get(DEFAULT_DIE);
      $$ = MathRollNode::ptr(new MathRollNode(
               RollNode::ptr(new DiceRollNode(roll)),
               RollNode::ptr(new IntRollNode($2)),
               MathRollNode::SUB)); }
*/
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
