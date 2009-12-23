#ifndef _FUNCDECL_H
#define	_FUNCDECL_H

#include "statement.h"
#include "expression.h"
#include <vector>
#include <string>


struct func {
    ~func();

    std::vector<std::string>    args;
    Statement*                  body;
    Expression*                 retExpr;
};



class FunctionDeclaration : public Statement {

public:
                    FunctionDeclaration (std::string funcName);
    virtual        ~FunctionDeclaration ()                              { if(function!=NULL) delete function; }

    virtual void    execute             ();

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



class FunctionCall : public Expression {
public:
                    FunctionCall        (std::string funcName, int lin, int col) : name(funcName), line(lin), column(col) { }
    virtual        ~FunctionCall        ();

    virtual double  evaluate            () const;

    virtual void    addValue            (Expression* val)               { values.push_back(val); }

protected:
    std::string     name;
    std::vector<Expression*>
                    values;
    int             line;
    int             column;

private:
                    FunctionCall        (const FunctionCall& src)       { }                 //DISABLED
    FunctionCall    operator=           (const FunctionCall& src)       { return *this; }   //DISABLED
};


#endif	/* _FUNCDECL_H */

