#ifndef _STATEMENT_H
#define	_STATEMENT_H

class Statement {
    
public:
    virtual            ~Statement       ()              { }
    virtual void        execute         () const = 0;
};

#endif	/* _STATEMENT_H */
