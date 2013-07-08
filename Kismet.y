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

%token NEWLINE
%token <string> DIE
%token <int> CONSTANT
%type <int> d_size

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
    CONSTANT
;
d_size:
    DIE
;
