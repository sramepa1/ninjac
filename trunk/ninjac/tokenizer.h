/*
 *      NINJAC - an interative, programmable calculator
 *
 *      semestral project for C/C++ programming course
 *      (Y36PJC) at the FEE CTU Prague
 *
 *      Created by Pavel Sramek (sramepa1@fel.cvut.cz)
 *      December 2009
 *
 *      This is free software, licensed under GNU LGPL
 *      (GNU Lesser General Public License, version 3)
 *      http://www.gnu.org/licenses/lgpl.html
 *
 *      Project homepage:
 *      http://code.google.com/p/ninjac/
 *
 *      Version 1.0
 *
 */
#ifndef _TOKENIZER_H
#define	_TOKENIZER_H

#include <map>
#include <string>
#include <iostream>

class Parser; // forward-declaration is enough - this file is included in parser.h

/*
 * A small structure to represent a lexeme
 */
struct Token {
            int         type;   // most important field - drives almost all switches
            std::string value;  // copied from input stream where necessary

            int         l;      // line of code in script source - used for exceptions

    unsigned int        argc;   // argument count (only meaningful for function tokens)
                                // - filled during Shunting-yard execution

    static const int    OPER = 1;//
    static const int    NUM = 2;
    static const int    FUNC = 3;
    static const int    LEFT_P = 4;//
    static const int    RIGHT_P = 5;
    static const int    ARG_SEP = 6;//
    static const int    VAR = 7;
    static const int    KEYWORD = 8;//
    static const int    STMT_SEP = 9;//
    static const int    ASSIGN = 10;//
    static const int    END = 11;
};


/*
 * Technically a part of the parser, this breaks the input stream into Tokens
 */
class Tokenizer {

public:
                        Tokenizer       (Parser* p);
                       ~Tokenizer       ();

    Token*              getToken        (std::istream& is, int& line); // main getter
    void                tokenOK         (); // transfer-of-ownership acknowledgement

    void                reset           ();

    bool                hasLTEpriority  (Token* first, Token* second); // a comparator

protected:
    int                 lastToken;
    Token*              cache;
    Parser*             parser;
    std::map<std::string,int> prior;

private:
                        Tokenizer       (const Tokenizer& src) { }              // DISABLED
    Tokenizer           operator=       (const Tokenizer& src) { return *this; } //DISABLED
};

#endif	/* _TOKENIZER_H */
