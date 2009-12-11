/* 
 * File:   constant.h
 * Author: Pavel
 *
 * Created on 11. prosinec 2009, 14:11
 */

#ifndef _CONSTANT_H
#define	_CONSTANT_H

class Constant : public Expression{
public:
                        Constant    (double val)            : value(val){}

    virtual double      evaluate    () const                {return value;}

protected:
    double value;
};

#endif	/* _CONSTANT_H */

