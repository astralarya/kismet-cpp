// Generated by Bisonc++ V4.01.00 on Thu, 02 Aug 2012 10:25:16 -0500

#ifndef KISMETparser_h_included
#define KISMETparser_h_included

// $insert baseclass
#include "KismetParserbase.h"
// $insert scanner.h
#include "KismetScanner.h"

// $insert namespace-open
namespace KISMET
{

#undef KismetParser
class KismetParser: public KismetParserBase
{
    // $insert scannerobject
    KismetScanner d_scanner;

    public:
        KismetParser(std::istream &in = std::cin):
        d_scanner(in){}

        int parse();

    private:
        void error(char const *msg);    // called on (syntax) errors
        int lex();                      // returns the next token from the
                                        // lexical scanner.
        void print();                   // use, e.g., d_token, d_loc

    // support functions for parse():
        void executeAction(int ruleNr);
        void errorRecovery();
        int lookup(bool recovery);
        void nextToken();
        void print__();
};

// $insert namespace-close
}

typedef KISMET::KismetParser KismetParser;

#endif
