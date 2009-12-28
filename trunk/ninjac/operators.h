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
#ifndef _OPERATOR_H
#define	_OPERATOR_H

#include <cstdlib>

#include "expression.h"

/*
 * Abstract ancestor of all the binary operators in my language
 */
class Operator : public Expression {

public:
                        Operator        ()              { left = right = NULL; }
    virtual            ~Operator        ();

    virtual void        setLeft         (Expression* l);
    virtual void        setRight        (Expression* r);

protected:
            Expression* left;
            Expression* right;
};



/*
 * Various subclasses - name says it all
 */

class PlusOperator : public Operator {
public:
    virtual double        evaluate      () const;
};

class MinusOperator : public Operator {
public:
    virtual double        evaluate      () const;
};

class MulOperator : public Operator {
public:
    virtual double        evaluate      () const;
};


/*
 * Division-like operators need to know their line in script source
 * to correctly report runtime exceptions (division by zero)
 */
class DivOperator : public Operator {
public:
                          DivOperator   (int line) : l(line) { }

    virtual double        evaluate      () const;

protected:
            int           l;
};

class IntDivOperator : public DivOperator {
public:
                          IntDivOperator (int line) : DivOperator(line) { }

    virtual double        evaluate      () const;
};

class ModuloOperator : public DivOperator {
public:
                          ModuloOperator (int line) : DivOperator(line) { }

    virtual double        evaluate      () const;
};

class AndOperator : public Operator {
public:
    virtual double        evaluate      () const;
};

class OrOperator : public Operator {
public:
    virtual double        evaluate      () const;
};

class EqualsOperator : public Operator {
public:
    virtual double        evaluate      () const;
};

class NotEqualsOperator : public Operator {
public:
    virtual double        evaluate      () const;
};

class LessOperator : public Operator {
public:
    virtual double        evaluate      () const;
};

class LTEOperator : public Operator {
public:
    virtual double        evaluate      () const;
};

class GreaterOperator : public Operator {
public:
    virtual double        evaluate      () const;
};

class GTEOperator : public Operator {
public:
    virtual double        evaluate      () const;
};

#endif	/* _OPERATOR_H */
