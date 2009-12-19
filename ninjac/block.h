#ifndef _BLOCK_H
#define	_BLOCK_H

#include <vector>

#include "statement.h"

class Block : public Statement {
public:
                        Block       ()                  {}
    virtual            ~Block       ();

    virtual void        execute     () const;
    
    virtual void        append      (Statement* s);

protected:
    std::vector<Statement*> statements;
};

#endif	/* _BLOCK_H */
