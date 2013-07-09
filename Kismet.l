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

[dD](%|[[:digit:]]+)    return KismetParser::DIE;
[[:digit:]]+/[dD]       return KismetParser::COUNT;
-[lL][[:digit:]]*       return KismetParser::DROP_LOW;
-[hH][[:digit:]]*       return KismetParser::DROP_HIGH;
[[:digit:]]+            return KismetParser::CONSTANT;
[[:alpha:]][][()<>{}[:alpha:][:space:]]*:          return KismetParser::LABEL;

"+"                     return KismetParser::ADD;
"-"                     return KismetParser::SUB;
"*"                     return KismetParser::MULT;
"/"                     return KismetParser::DIV;
"("                     return KismetParser::R_PAREN;
")"                     return KismetParser::L_PAREN;
\n                      return KismetParser::NEWLINE;
^exit$                  if(Options::Instance()->get(INTERACTIVE)) return EOF;
[[:space:]]             /* empty */
.                       /* empty */
