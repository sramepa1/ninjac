#ifndef _VARIABLE_H
#define	_VARIABLE_H

#include <string>

#include "expression.h"

class Variable : public Expression {

public:
                    Variable    (std::string name) : n(name)    { }
                    
    virtual double  evaluate    () const;

protected:
    std::string     n;
};


#endif	/* _VARIABLE_H */

