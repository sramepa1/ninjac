#ifndef _EXITSTMT_H
#define	_EXITSTMT_H

#include "statement.h"
#include "ninjacexcept.h"

class ExitStatement : public Statement {
public:
    virtual void    execute ()  { throw ExitException(); }
};

#endif	/* _EXITSTMT_H */

