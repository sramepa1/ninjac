#ifndef _OPERATOR_H
#define	_OPERATOR_H

#include <cstdlib>

#include "expression.h"

class Operator : public Expression {

public:
                        Operator    ()              { left = right = NULL; }
    virtual            ~Operator    ();

    virtual void        setLeft     (Expression* l);
    virtual void        setRight    (Expression* r);

protected:
            Expression* left;
            Expression* right;
};



class PlusOperator : public Operator {
public:
    virtual double        evaluate    () const;
};

class MinusOperator : public Operator {
public:
    virtual double        evaluate    () const;
};

class MulOperator : public Operator {
public:
    virtual double        evaluate    () const;
};

class DivOperator : public Operator {
public:
                          DivOperator (int line, int column) : l(line), c(column) { }

    virtual double        evaluate    () const;

protected:
            int           l;
            int           c;
};

class IntDivOperator : public DivOperator {
public:
                          IntDivOperator (int line, int column) : DivOperator(line,column) { }

    virtual double        evaluate    () const;
};

class ModuloOperator : public DivOperator {
public:
                          ModuloOperator (int line, int column) : DivOperator(line,column) { }

    virtual double        evaluate    () const;
};

class AndOperator : public Operator {
public:
    virtual double        evaluate    () const;
};

class OrOperator : public Operator {
public:
    virtual double        evaluate    () const;
};

class EqualsOperator : public Operator {
public:
    virtual double        evaluate    () const;
};

class NotEqualsOperator : public Operator {
public:
    virtual double        evaluate    () const;
};

class LessOperator : public Operator {
public:
    virtual double        evaluate    () const;
};

class LTEOperator : public Operator {
public:
    virtual double        evaluate    () const;
};

class GreaterOperator : public Operator {
public:
    virtual double        evaluate    () const;
};

class GTEOperator : public Operator {
public:
    virtual double        evaluate    () const;
};

#endif	/* _OPERATOR_H */
