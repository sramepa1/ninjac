#ifndef _BUILTIN_H
#define	_BUILTIN_H

#include <cmath>

#include "expression.h"
#include "globals.h"
#include "variable.h"

class BuiltInPi : public Expression {
public:
    virtual double evaluate () const { return M_PI; }
};

class BuiltInE : public Expression {
public:
    virtual double evaluate () const { return M_E; }
};

class BuiltInNot : public Expression {
public:
    virtual double evaluate () const { return (double)(Variable("firstarg").evaluate() <= Globals::inst->delta); }
};

class BuiltInSqrt : public Expression {
public:
    virtual double evaluate () const { return sqrt(Variable("firstarg").evaluate()); }
};

class BuiltInAbs : public Expression {
public:
    virtual double evaluate () const { return fabs(Variable("firstarg").evaluate()); }
};

class BuiltInRound : public Expression {
public:
    virtual double evaluate () const { return round(Variable("firstarg").evaluate()); }
};

class BuiltInSin : public Expression {
public:
    virtual double evaluate () const { return sin(Variable("firstarg").evaluate()); }
};

class BuiltInCos : public Expression {
public:
    virtual double evaluate () const { return cos(Variable("firstarg").evaluate()); }
};

class BuiltInTan : public Expression {
public:
    virtual double evaluate () const { return tan(Variable("firstarg").evaluate()); }
};

class BuiltInASin : public Expression {
public:
    virtual double evaluate () const { return asin(Variable("firstarg").evaluate()); }
};

class BuiltInACos : public Expression {
public:
    virtual double evaluate () const { return acos(Variable("firstarg").evaluate()); }
};

class BuiltInATan : public Expression {
public:
    virtual double evaluate () const { return atan(Variable("firstarg").evaluate()); }
};

class BuiltInLog : public Expression {
public:
    virtual double evaluate () const { return log10(Variable("firstarg").evaluate()); }
};

class BuiltInLn : public Expression {
public:
    virtual double evaluate () const { return log(Variable("firstarg").evaluate()); }
};

class BuiltInExp : public Expression {
public:
    virtual double evaluate () const { return exp(Variable("firstarg").evaluate()); }
};

class BuiltInSgn : public Expression {
public:
    virtual double evaluate () const { double d=Variable("firstarg").evaluate(); return fabs(d)<=Globals::inst->delta ? 0.0 : d/fabs(d); }
};

class BuiltInPow : public Expression {
public:
    virtual double evaluate () const { return pow(Variable("firstarg").evaluate(),Variable("secondarg").evaluate()); }
};

class BuiltInMax : public Expression {
public:
    virtual double evaluate () const { double f=Variable("firstarg").evaluate();double s=Variable("secondarg").evaluate();return f>s?f:s; }
};

class BuiltInMin : public Expression {
public:
    virtual double evaluate () const { double f=Variable("firstarg").evaluate();double s=Variable("secondarg").evaluate();return f<s?f:s; }
};

#endif	/* _BUILTIN_H */

