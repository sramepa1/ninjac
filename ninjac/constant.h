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
#ifndef _CONSTANT_H
#define	_CONSTANT_H

/*
 * Represents constant expression (decimal number literal)
 */
class Constant : public Expression{
    
public:
                        Constant    (double val)    : value(val)    { }

    virtual double      evaluate    () const                        { return value; }

protected:
    double value;
};

#endif	/* _CONSTANT_H */
