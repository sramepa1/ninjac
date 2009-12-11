/* 
 * File:   block.h
 * Author: Pavel
 *
 * Created on 9. prosinec 2009, 16:07
 */

#ifndef _BLOCK_H
#define	_BLOCK_H

#include "statement.h"
#include <vector>


class Block : public Statement {
public:
                        Block       () {}
    virtual            ~Block       ();

    virtual void        execute     () const;
    virtual void        append      (Statement* s);

protected:
    std::vector<Statement*> statements;
};

#endif	/* _BLOCK_H */
