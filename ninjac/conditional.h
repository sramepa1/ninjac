#ifndef _CONDITIONAL_H
#define	_CONDITIONAL_H

#include <cstdlib>

#include "statement.h"
#include "expression.h"

class Conditional : public Statement {

public:
                            Conditional (bool top) : topLevel(top)  { cond=NULL; ifTrue=ifFalse=NULL; }
    virtual                ~Conditional ();

    virtual void            execute     ();

    virtual void            setCondition(Expression* condition)     { cond=condition; }
    virtual void            setIfTrue   (Statement* stmt)           { ifTrue=stmt; }
    virtual void            setIfFalse  (Statement* stmt)           { ifFalse=stmt; }

protected:
            Expression*     cond;
            Statement*      ifTrue;
            Statement*      ifFalse;

            bool            topLevel;

private:
                            Conditional (const Conditional& src)    { } //DISABLED
            Conditional     operator=   (const Conditional& src)    { return *this; } //DISABLED
};

#endif	/* _CONDITIONAL_H */
