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
#ifndef _EXITSTMT_H
#define	_EXITSTMT_H

#include "statement.h"
#include "ninjacexcept.h"

/*
 * Represents the 'exit' statement
 */
class ExitStatement : public Statement {
public:
    virtual void    execute ()  { throw ExitException(); }
};

#endif	/* _EXITSTMT_H */
