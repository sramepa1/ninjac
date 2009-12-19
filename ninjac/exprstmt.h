/* 
 * File:   exprstmt.h
 * Author: Pavel
 *
 * Created on 11. prosinec 2009, 14:17
 */

#ifndef _EXPRSTMT_H
#define	_EXPRSTMT_H

#include "statement.h"
#include "expression.h"

class ExpressionStatement : public Statement{
public:
                        ExpressionStatement (Expression* expr)      : expression(expr) {}
    virtual            ~ExpressionStatement ()                      {delete expression;}

    virtual void        execute             () const;

protected:
    Expression* expression;
};

#endif	/* _EXPRSTMT_H */