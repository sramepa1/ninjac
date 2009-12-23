#ifndef _EXPRSTMT_H
#define	_EXPRSTMT_H

#include <cstdlib>

#include "statement.h"
#include "expression.h"

class ExprStatement : public Statement{
    
public:
                        ExprStatement       ()                  { expression = NULL; }
    virtual            ~ExprStatement       ()                  { if(expression != NULL) delete expression; }

    virtual void        setExpr             (Expression* expr);

protected:
    Expression* expression;
};



class ExpressionStatement : public ExprStatement {

public:
                        ExpressionStatement () : ExprStatement()    { }
    virtual void        execute             ();

private:
                        ExpressionStatement (const ExpressionStatement& src)    { }               //DISABLED
    ExpressionStatement operator=           (const ExpressionStatement& src)    { return *this; } //DISABLED
};




class PrintStatement : public ExprStatement {

public:
                        PrintStatement      () : ExprStatement()    { }
    virtual void        execute             ();

private:
                        PrintStatement      (const PrintStatement& src)         { }               //DISABLED
    PrintStatement      operator=           (const PrintStatement& src)         { return *this; } //DISABLED
};

#endif	/* _EXPRSTMT_H */
