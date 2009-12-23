#ifndef _ASSIGNMENT_H
#define	_ASSIGNMENT_H

#include <string>

#include "statement.h"
#include "expression.h"

class Assignment : public Statement {

public:
                            Assignment  (std::string varName) : vName(varName)  { val=NULL; }
    virtual                ~Assignment  ()                      { if(val != NULL) delete val; }

    virtual void            execute     ();

    virtual void            setValue    (Expression* value);

protected:
            std::string     vName;
            Expression*     val;

private:
                            Assignment  (const Assignment& src) { } //DISABLED
            Assignment      operator=   (const Assignment& src) { return *this; } //DISABLED
};



#endif	/* _ASSIGNMENT_H */

