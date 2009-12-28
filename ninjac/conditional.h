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
#ifndef _CONDITIONAL_H
#define	_CONDITIONAL_H

#include <cstdlib>

#include "statement.h"
#include "expression.h"

/*
 * Represents conditional statement (if <condition> then <statement> [else <statement>])
 */
class Conditional : public Statement {

public:
                            Conditional (bool top) : topLevel(top)  { cond=NULL; ifTrue=ifFalse=NULL; }
    virtual                ~Conditional ();

    virtual void            execute     ();

    virtual void            setCondition(Expression* condition)     { cond=condition; }
    virtual void            setIfTrue   (Statement* stmt)           { ifTrue=stmt; }
    virtual void            setIfFalse  (Statement* stmt)           { ifFalse=stmt; }

protected:
            Expression*     cond;
            Statement*      ifTrue;
            Statement*      ifFalse;

            bool            topLevel;

private:
                            Conditional (const Conditional& src)    { } //DISABLED
            Conditional     operator=   (const Conditional& src)    { return *this; } //DISABLED
};

#endif	/* _CONDITIONAL_H */
