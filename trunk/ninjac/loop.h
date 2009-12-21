#ifndef _LOOP_H
#define	_LOOP_H

#include "statement.h"
#include "variable.h"


class Loop : public Statement {

public:
                        Loop            () : stmt(NULL)                 { }
    virtual            ~Loop            ()                              { if(stmt != NULL) delete stmt;}

    virtual void        setStatement    (Statement* statement)          { stmt=statement; }

protected:
            Statement*  stmt;
};



class ForLoop : public Loop {

public:
                        ForLoop         (std::string varName) : vName(varName) { fromExpr=toExpr=stepExpr=NULL; }
   virtual             ~ForLoop         ();

   virtual  void        execute         () const;

   virtual  void        setFrom         (Expression* fromExpression)    { fromExpr=fromExpression; }
   virtual  void        setTo           (Expression* toExpression)      { toExpr=toExpression; }
   virtual  void        setStep         (Expression* stepExpression)    { stepExpr=stepExpression; }

protected:
            std::string vName;

            Expression* fromExpr;
            Expression* toExpr;
            Expression* stepExpr;

            double      from;
            double      to;
            double      step;

private:
                        ForLoop         (const ForLoop& src)            { } //DISABLED
            ForLoop     operator=       (const ForLoop& src)            { return *this; } //DISABLED
};



class CondLoop : public Loop {

public:
                        CondLoop        ()                              { cond=NULL; }
    virtual            ~CondLoop        ()                              { if(cond!=NULL) delete cond; }
    virtual void        setCond         (Expression* condition)         { cond = condition; }

protected:
            Expression* cond;
};



class DoLoop : public CondLoop {

public:
    virtual void        execute         () const;

private:
                        DoLoop          (const DoLoop& src)             { }  //DISABLED
            DoLoop      operator=       (const DoLoop& src)             { return *this; } //DISABLED
};



class WhileLoop : public CondLoop {

public:
    virtual void        execute         () const;

private:
                        WhileLoop       (const WhileLoop& src)          { } //DISABLED
            WhileLoop   operator=       (const WhileLoop& src)          { return *this; } //DISABLED
};

#endif	/* _LOOP_H */
