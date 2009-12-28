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
#ifndef _FUNCDECL_H
#define	_FUNCDECL_H

#include <vector>
#include <string>

#include "statement.h"
#include "expression.h"

/*
 * A simple struct to be put to the function table
 */
struct func {
                               ~func();

    std::vector<std::string>    args;
    Statement*                  body;
    Expression*                 retExpr;
};


/*
 * Represents the function declaration statement
 */
class FunctionDeclaration : public Statement {

public:
                    FunctionDeclaration (std::string funcName);
    virtual        ~FunctionDeclaration ()                              { if(function!=NULL) delete function; }

    virtual void    execute             ();

    virtual bool    hasArgument         (std::string arg);

    virtual void    addArgument         (std::string arg);
    virtual void    setBody             (Statement* body);
    virtual void    setReturn           (Expression* expr);

protected:
    std::string     name;
    func*           function;

private:
                        FunctionDeclaration (const FunctionDeclaration& src)     { }                //DISABLED
    FunctionDeclaration operator=           (const FunctionDeclaration& src)     { return *this; }  //DISABLED
};




/*
 * Represents the function call, which is an expression
 */
class FunctionCall : public Expression {
public:
                    FunctionCall        (std::string funcName, int lin) : name(funcName), line(lin) { }
    virtual        ~FunctionCall        ();

    virtual double  evaluate            () const;

    virtual void    addValue            (Expression* val)               { values.push_back(val); }

protected:
    std::string     name;
    std::vector<Expression*>
                    values;
    int             line;

private:
                    FunctionCall        (const FunctionCall& src)       { }                 //DISABLED
    FunctionCall    operator=           (const FunctionCall& src)       { return *this; }   //DISABLED
};


#endif	/* _FUNCDECL_H */
