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
             modifier: MultiRollNode::modifier;
             modifier_list: MultiRollNode::mod_list;
             directive_type: Roll;

%left NEWLINE
%left COMMA
%left ADD SUB
%left MULT DIV
%right UNARY
%token R_PAREN L_PAREN
%token <string> DIE LABEL DROP_LOW DROP_HIGH
%token <integer> COUNT CONSTANT
%type <integer> count constant die drop_low drop_high
%type <string> label
%type <die_type> roll
%type <modifier> modifier
%type <modifier_list> modlist
%type <roll_type> expr leaf modpair
%type <directive_type> directive

%%
/* rules */

input:
    /* empty */
  | input line
    { if(Options::Instance()->get(INTERACTIVE)) std::cout << '>' << std::flush; }
;
line:
    NEWLINE
  | directive NEWLINE
    { ($1).roll();
      std::cout << ($1).print() << std::endl; }
  | error NEWLINE
;
directive:
    expr
    { $$ = Roll($1); }
  | label expr
    { $$ = Roll($2,$1); }
  | label
    { ($$).setLabel($1); }
;
expr:
    leaf
    { $$ = std::move($1); }
  | expr ADD expr
    { $$ = MathRollNode::ptr(new MathRollNode(std::move($1),std::move($3),MathRollNode::ADD)); }
  | expr SUB expr
    { $$ = MathRollNode::ptr(new MathRollNode(std::move($1),std::move($3),MathRollNode::SUB)); }
  | expr MULT expr
    { $$ = MathRollNode::ptr(new MathRollNode(std::move($1),std::move($3),MathRollNode::MULT)); }
  | expr DIV expr
    { $$ = MathRollNode::ptr(new MathRollNode(std::move($1),std::move($3),MathRollNode::DIV)); }
  | R_PAREN expr L_PAREN
    { $$ = ParensRollNode::ptr(new ParensRollNode(std::move($2))); }
  | modpair
    { $$ = std::move($1); }
;
modpair:
    expr modlist
    { $$ = MultiRollNode::ptr(new MultiRollNode(std::move($1),std::move($2))); }
  | modlist
    { $$ = MultiRollNode::ptr(new MultiRollNode(RollNode::ptr(new DiceRollNode()),std::move($1))); }
;
modlist:
    modifier
    { ($$).emplace_back(std::move($1)); }
  | modlist COMMA modifier
    { ($1).emplace_back(std::move($3));
      $$ = MultiRollNode::copy_modlist($1); }
;
modifier:
    ADD expr %prec UNARY
    { ($$).setArgument(std::move($2));
      ($$).op = MathRollNode::ADD; }
  | SUB expr %prec UNARY
    { ($$).argument = std::move($2);
      ($$).op = MathRollNode::SUB; }
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
    { ($$).die = $1; }
  | count
    { ($$).times = $1; }
  | drop_low
    { ($$).low = $1; }
  | drop_high
    { ($$).high = $1; }
  | roll drop_low
    { ($$).low = $2; }
  | roll drop_high
    { ($$).high = $2; }
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
drop_low:
    DROP_LOW
    { std::stringstream ss;
      ss << d_scanner.matched().substr(2);
      if(ss.str().size())
          ss >> $$;
      else
          $$ = 1; }
;
drop_high:
    DROP_HIGH
    { std::stringstream ss;
      ss << d_scanner.matched().substr(2);
      if(ss.str().size())
          ss >> $$;
      else
          $$ = 1; }
;
die:
    DIE
    { std::stringstream ss;
      ss << d_scanner.matched().substr(1); 
      if(ss.str() == "%")
          $$ = 100;
      else
          ss >> $$; }
;
label:
    LABEL
    { $$ = d_scanner.matched().substr(0,d_scanner.matched().size()-1); }
;
