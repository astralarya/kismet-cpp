/*
Kismet.l
Flexc++ input file
Mara Kim
*/

%namespace = KISMET
%class-name = KismetScanner
%lex-source = "KismetScanner.cc"


LINECOMMENT_S           "//"
MULTILINECOMMENT_S      "/*"
MULTILINECOMMENT_E      "*/"

%x ASSIGN MULTILINECOMMENT STRING INCLUDE

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

"+"                     return KismetParser::PLUS;
"-"                     return KismetParser::MINUS;
\n                      return KismetParser::NEWLINE;
[[:space:]]             /* empty */
.                       /* empty */
