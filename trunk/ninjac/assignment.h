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
#ifndef _ASSIGNMENT_H
#define	_ASSIGNMENT_H

#include <string>

#include "statement.h"
#include "expression.h"

/*
 * Represents assignment statement (set $var : <expression>)
 */
class Assignment : public Statement {

public:
                            Assignment  (std::string varName, bool top) : vName(varName),topLevel(top) { val=NULL; }
    virtual                ~Assignment  ()                      { if(val != NULL) delete val; }

    virtual void            execute     ();

    virtual void            setValue    (Expression* value);

protected:
            std::string     vName;
            Expression*     val;

            bool            topLevel;

private:
                            Assignment  (const Assignment& src) { } //DISABLED
            Assignment      operator=   (const Assignment& src) { return *this; } //DISABLED
};

#endif	/* _ASSIGNMENT_H */
