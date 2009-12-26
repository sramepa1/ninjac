#ifndef _PARSER_H
#define	_PARSER_H

#include <iostream>
#include <string>
#include <set>
#include <queue>
#include <stack>

#include "tokenizer.h"
#include "statement.h"
#include "expression.h"
#include "operators.h"

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

    Statement*              parseKeyword(std::istream& is);
    void                    expect      (std::string keyword, std::istream& is);
    std::string             parseVar    (std::istream& is);

    Statement*              parseAssign (std::istream& is);
    Statement*              parseBlock  (std::istream& is);
    Statement*              parseFor    (std::istream& is);
    Statement*              parseWhile  (std::istream& is);
    Statement*              parseRepeat (std::istream& is);
    Statement*              parseFunc   (std::istream& is);
    Statement*              parseIf     (std::istream& is);

    void                    shuntingYard(std::istream& is, std::queue<Token*>& out);
    Operator*               getOperator (std::string oper, int l);

    void                    clearTokens (std::stack<Token*>& stack, std::queue<Token*>& queue);
    void                    clearExprs  (std::stack<Expression*>& stack, std::queue<Token*>& queue);

    Tokenizer*              tok;

    std::set<std::string>   keywords;
    std::set<std::string>   twoCharOper;
    std::string             oneCharOper;

    int                     line;
    bool                    topLevel;
};

#endif	/* _PARSER_H */
