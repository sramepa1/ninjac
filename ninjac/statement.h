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
#ifndef _STATEMENT_H
#define	_STATEMENT_H

/*
 * This would be an interface in Java - common ancestor to all statement objects
 * (those wich can return be executed)
 */
class Statement {
    
public:
    virtual            ~Statement       ()              { }
    virtual void        execute         () = 0;
};

#endif	/* _STATEMENT_H */
