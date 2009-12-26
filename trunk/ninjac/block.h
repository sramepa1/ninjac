#ifndef _BLOCK_H
#define	_BLOCK_H

#include <vector>

#include "statement.h"

class Block : public Statement {
    
public:
                        Block       (bool top) : topLevel(top)  { }
    virtual            ~Block       ();

    virtual void        execute     ();
    
    virtual void        append      (Statement* s);

protected:
    std::vector<Statement*> statements;
    bool                    topLevel;

private:
                        Block       (const Block& src)          { }                 //DISABLED
    Block               operator=   (const Block& src)          { return *this; }   //DISABLED
};

#endif	/* _BLOCK_H */
