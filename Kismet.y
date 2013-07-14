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
             float_type: double;
             die_type: Dice::roll_type;
             atom: RollNode::atom;
             atom_list: RollNode::atom_list;
             enum_roll: EnumRollNode::enum_roll;
             modifier: MultiRollNode::modifier;
             modifier_list: MultiRollNode::mod_list;
             roll_type: RollNode::ptr;
             directive_type: Roll;

%left NEWLINE
%left COMMA
%left ADD SUB
%left MULT DIV
%token R_PAREN L_PAREN R_COUNTEXPR L_COUNTEXPR R_DIEEXPR L_DIEEXPR
%token <string> DIE LABEL DROP_LOW DROP_HIGH STRING
%token <integer> COUNT
%token <float_type> NUMBER
%type <integer> count die drop_low drop_high
%type <float_type> number
%type <string> label
%type <die_type> roll
%type <atom> constant
%type <atom_list> enumlist enumdie
%type <enum_roll> enumroll
%type <modifier> modifier modfactor
%type <modifier_list> modlist
%type <roll_type> expr factor leaf modpair countexpr rolldie enumrolldie
%type <directive_type> directive

%%
/* rules */

input:
    /* empty */
  | input line
  | error NEWLINE
;
line:
    NEWLINE
  | directive NEWLINE
    { ($1).roll();
      std::cout << ($1).print() << std::endl; }
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
    factor
    { $$ = std::move($1); }
  | modpair
    { $$ = std::move($1); }
  | expr COMMA expr
    { ListRollNode* node = (new ListRollNode());
      node->insert(std::move($1));
      node->insert(std::move($3));
      $$ = RollNode::ptr(node); }
;
factor:
    leaf
    { $$ = std::move($1); }
  | R_PAREN expr L_PAREN
    { $$ = ParensRollNode::ptr(new ParensRollNode(std::move($2))); }
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
    modfactor
    { $$ = std::move($1); }
  | ADD expr
    { ($$).setArgument(std::move($2));
      ($$).op = MathRollNode::ADD; }
  | SUB expr
    { ($$).argument = std::move($2);
      ($$).op = MathRollNode::SUB; }
;
modfactor:
    MULT factor
    { ($$).setArgument(std::move($2));
      ($$).op = MathRollNode::MULT; }
  | DIV factor
    { ($$).setArgument(std::move($2));
      ($$).op = MathRollNode::DIV; }
;
leaf:
    constant
    { $$ = ConstRollNode::ptr(new ConstRollNode($1)); }
  | rolldie
    { $$ = std::move($1); }
  | enumrolldie
    { $$ = std::move($1); }
;
rolldie:
    roll
    { $$ = DiceRollNode::ptr(new DiceRollNode($1)); }
  | count roll
    { ($2).times = $1;
      $$ = DiceRollNode::ptr(new DiceRollNode($2)); }
  | count
    { Dice::roll_type d;
      d.times = $1;
      $$ = DiceRollNode::ptr(new DiceRollNode(d)); }
  | countexpr roll
    { $$ = ExprDiceRollNode::ptr(new ExprDiceRollNode(std::move($1),DiceRollNode::ptr(new DiceRollNode($2)))); }
;
enumrolldie:
    enumroll
    { $$ = DiceRollNode::ptr(new EnumRollNode($1)); }
  | count enumroll
    { ($2).die.times = $1;
      $$ = DiceRollNode::ptr(new EnumRollNode($2)); }
  | countexpr enumroll
    { $$ = ExprDiceRollNode::ptr(new ExprDiceRollNode(std::move($1),DiceRollNode::ptr(new EnumRollNode($2)))); }
;
roll:
    die
    { ($$).die = $1; }
  | roll drop_low
    { ($$).low = $2; }
  | roll drop_high
    { ($$).high = $2; }
;
countexpr:
    R_COUNTEXPR expr L_COUNTEXPR
    { $$ = std::move($2); }
;
enumroll:
    enumdie
    { ($$).enumerator = $1; }
  | enumroll drop_low
    { ($1).die.low = $2; }
  | enumroll drop_high
    { ($1).die.high = $2; }
;
enumdie:
    R_DIEEXPR enumlist L_DIEEXPR
    { $$ = $2; }
;
enumlist:
    constant
    { ($$).push_back($1); }
  | enumlist COMMA constant
    { ($1).push_back($3);
      $$ = $1; }
;
constant:
    number
    { $$ = RollNode::atom($1); }
  | STRING
    { $$ = RollNode::atom($1); }
;
number:
    NUMBER
    { std::stringstream ss;
      ss << d_scanner.matched();
      ss >> $$; }
;
count:
    COUNT
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
