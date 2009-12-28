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
#ifndef _VARIABLE_H
#define	_VARIABLE_H

#include <string>

#include "expression.h"

/*
 * Represents an instance of a variable in/as an expression
 */
class Variable : public Expression {

public:
                    Variable    (std::string name) : n(name)    { }
                    
    virtual double  evaluate    () const;

protected:
    std::string     n;
};

#endif	/* _VARIABLE_H */
