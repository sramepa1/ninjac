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
#ifndef _BLOCK_H
#define	_BLOCK_H

#include <vector>

#include "statement.h"

/*
 * Represents block statement (begin ... end)
 */
class Block : public Statement {
    
public:
                        Block       (bool top) : topLevel(top)  { }
    virtual            ~Block       ();

    virtual void        execute     ();
    
    virtual void        append      (Statement* s);

protected:
    std::vector<Statement*> statements;
    bool                    topLevel;

private:
                        Block       (const Block& src)          { }                 //DISABLED
    Block               operator=   (const Block& src)          { return *this; }   //DISABLED
};

#endif	/* _BLOCK_H */
