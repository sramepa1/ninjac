/* 
 * File:   statement.h
 * Author: Pavel
 *
 * Created on 9. prosinec 2009, 16:02
 */

#ifndef _STATEMENT_H
#define	_STATEMENT_H

class Statement {
public:
    virtual            ~Statement       () {}
    virtual void        execute         () const = 0;
};

#endif	/* _STATEMENT_H */

