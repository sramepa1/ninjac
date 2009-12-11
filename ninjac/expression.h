/* 
 * File:   expression.h
 * Author: Pavel
 *
 * Created on 9. prosinec 2009, 16:02
 */

#ifndef _EXPRESSION_H
#define	_EXPRESSION_H

class Expression {
public:
    virtual            ~Expression      () {}
    virtual double      evaluate        () const = 0;
};


#endif	/* _EXPRESSION_H */

