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
#ifndef _EXPRESSION_H
#define	_EXPRESSION_H

/*
 * This would be an interface in Java - common ancestor to all expression objects
 * (those wich can return a value)
 */
class Expression {
    
public:
    virtual            ~Expression      ()              { }
    virtual double      evaluate        () const = 0;
};

#endif	/* _EXPRESSION_H */
