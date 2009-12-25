#ifndef _TOKENIZER_H
#define	_TOKENIZER_H

#include <map>
#include <string>
#include <iostream>

class Parser;

struct Token {
            int         type;
            std::string value;

            int         l;
            int         c;

    unsigned int        argc;

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



class Tokenizer {

public:
                        Tokenizer       (Parser* p);
                       ~Tokenizer       ();

    Token*              getToken        (std::istream& is, int& column, int& line);
    void                tokenOK         ();

    void                reset           ();

    bool                hasLTEpriority  (Token* first, Token* second);

protected:
    int                 lastToken;
    Token*              cache;
    Parser*             parser;
    std::map<std::string,int> prior;
};


#endif	/* _TOKENIZER_H */

