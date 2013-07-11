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

%x MULTILINECOMMENT WAITING

/* rules */
%%

{LINECOMMENT_S}.*

{MULTILINECOMMENT_S}    begin(StartCondition__::MULTILINECOMMENT);
<MULTILINECOMMENT>{
    {MULTILINECOMMENT_E}    begin(StartCondition__::INITIAL);
    .                   /* empty */
    \n                  return KismetParser::NEWLINE;
}

<WAITING>{
    "..["               begin(StartCondition__::INITIAL);
    .                   /* empty */
    \n                  return KismetParser::NEWLINE;
}
"]"                     if(Options::Instance()->get(REACTIVE)) begin(StartCondition__::WAITING);

[dD](%|[[:digit:]]+)    return KismetParser::DIE;
[[:digit:]]+/[dD]       return KismetParser::COUNT;
"{"/([^}]+"}"[dD])      return KismetParser::R_COUNTEXPR;
"}"/[dD]                return KismetParser::L_COUNTEXPR;
[dD]"{"                 return KismetParser::R_DIEEXPR;
"}"                     return KismetParser::L_DIEEXPR;
[[:alpha:]]+            return KismetParser::ENUM;
-[lL][[:digit:]]*       return KismetParser::DROP_LOW;
-[hH][[:digit:]]*       return KismetParser::DROP_HIGH;
[[:digit:]]+            return KismetParser::CONSTANT;
[[:alpha:]][()<>{}[:alpha:][:space:]]*:          return KismetParser::LABEL;

"+"             return KismetParser::ADD;
"-"             return KismetParser::SUB;
"*"             return KismetParser::MULT;
"/"             return KismetParser::DIV;
"("             return KismetParser::R_PAREN;
")"             return KismetParser::L_PAREN;
","             return KismetParser::COMMA;
\n              return KismetParser::NEWLINE;
^[[:space:]]*exit[[:space:]]*$                  if(Options::Instance()->get(INTERACTIVE)) return EOF; // Interactive exit
[[:space:]]             /* empty */
.                       /* empty */
