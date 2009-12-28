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
#ifndef _EXPRSTMT_H
#define	_EXPRSTMT_H

#include <cstdlib> // for the NULL macro

#include "statement.h"
#include "expression.h"

/*
 * Abstract ancestor of all the statements holding nothing but an expression
 */
class ExprStatement : public Statement{
    
public:
                        ExprStatement       ()                  { expression = NULL; }
    virtual            ~ExprStatement       ()                  { if(expression != NULL) delete expression; }

    virtual void        setExpr             (Expression* expr);

protected:
    Expression* expression;
};


/*
 * Represents an expression acting as a statement
 */
class ExpressionStatement : public ExprStatement {

public:
                        ExpressionStatement () : ExprStatement()    { }
    virtual void        execute             ();

private:
                        ExpressionStatement (const ExpressionStatement& src)    { }               //DISABLED
    ExpressionStatement operator=           (const ExpressionStatement& src)    { return *this; } //DISABLED
};



/*
 * Represents the 'print <expression>' statement
 */
class PrintStatement : public ExprStatement {

public:
                        PrintStatement      () : ExprStatement()    { }
    virtual void        execute             ();

private:
                        PrintStatement      (const PrintStatement& src)         { }               //DISABLED
    PrintStatement      operator=           (const PrintStatement& src)         { return *this; } //DISABLED
};


/*
 * Represents the 'precision <expression>' statement
 */
class PrecisionStatement : public ExprStatement {

public:
                        PrecisionStatement  () : ExprStatement()    { }
    virtual void        execute             ();

private:
                        PrecisionStatement  (const PrecisionStatement& src)     { }               //DISABLED
    PrecisionStatement  operator=           (const PrecisionStatement& src)     { return *this; } //DISABLED
};

#endif	/* _EXPRSTMT_H */
