/*
Kismet.l
Flexc++ input file
Mara Kim
*/

%namespace = KISMET
%class-name = KismetScanner
%lex-source = "KismetScanner.cc"
%interactive


LINECOMMENT_S           "//"
MULTILINECOMMENT_S      "/*"
MULTILINECOMMENT_E      "*/"

%x MULTILINECOMMENT

/* rules */
%%

{LINECOMMENT_S}.*

{MULTILINECOMMENT_S}    begin(StartCondition__::MULTILINECOMMENT);
<MULTILINECOMMENT>{
    {MULTILINECOMMENT_E}    begin(StartCondition__::INITIAL);
    .|\n
}

d[[:digit:]]+           return KismetParser::DIE;
[[:digit:]]+/d          return KismetParser::COUNT;
[[:digit:]]+            return KismetParser::CONSTANT;
[[:alpha:]][[:alpha:][:space:]]+:          return KismetParser::LABEL;

"+"                     return KismetParser::ADD;
"-"                     return KismetParser::SUB;
"*"                     return KismetParser::MULT;
"/"                     return KismetParser::DIV;
\n                      return KismetParser::NEWLINE;
^exit$                  return EOF;
[[:space:]]             /* empty */
.                       /* empty */
