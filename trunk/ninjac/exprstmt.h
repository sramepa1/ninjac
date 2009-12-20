#ifndef _EXPRSTMT_H
#define	_EXPRSTMT_H

#include <cstdlib>

#include "statement.h"
#include "expression.h"

class ExpressionStatement : public Statement{
public:
                        ExpressionStatement ()                  { expression = NULL; }
    virtual            ~ExpressionStatement ()                  { if(expression != NULL) delete expression; }

    virtual void        execute             () const;

    virtual void        setExpr             (Expression* expr);

protected:
    Expression* expression;

private:
                        ExpressionStatement (const ExpressionStatement& src)  { }               //DISABLED
    ExpressionStatement operator=           (const ExpressionStatement& src)  { return *this; } //DISABLED
};

#endif	/* _EXPRSTMT_H */
