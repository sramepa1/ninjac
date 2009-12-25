#ifndef _PARSER_H
#define	_PARSER_H

#include <iostream>
#include <string>
#include <set>
#include <queue>

#include "tokenizer.h"
#include "statement.h"
#include "expression.h"
#include "operator.h"

class Parser {
    
public:
                            Parser      ();
                           ~Parser      ();

    void                    parse       (std::istream& is);
    void                    reset       ();

    friend class            Tokenizer;

protected:
    Expression*             parseExpr   (std::istream& is);
    Statement*              parseStmt   (std::istream& is);

    void                    shuntingYard(std::istream& is, std::queue<Token*>& out);
    Operator*               getOperator (std::string oper, int l, int c);

    Tokenizer*              tok;

    std::set<std::string>   keywords;
    std::set<std::string>   twoCharOper;
    std::string             oneCharOper;

    int                     line;
    int                     column;
};

#endif	/* _PARSER_H */
