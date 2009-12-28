/*
 *      NINJAC - an interative, programmable calculator
 *
 *      semestral project for C/C++ programming course
 *      (Y36PJC) at the FEE CTU Prague
 *
 *      Created by Pavel Sramek (sramepa1@fel.cvut.cz)
 *      December 2009
 *
 *      This is free software, licensed under GNU LGPL
 *      (GNU Lesser General Public License, version 3)
 *      http://www.gnu.org/licenses/lgpl.html
 *
 *      Project homepage:
 *      http://code.google.com/p/ninjac/
 *
 *      Version 1.0
 *
 */
#ifndef _LOOP_H
#define	_LOOP_H

#include "statement.h"
#include "variable.h"


/*
 * Abstract ancestor of all loop statements
 */
class Loop : public Statement {

public:
                        Loop            (bool top) : stmt(NULL),topLevel(top) { }
    virtual            ~Loop            ()                              { if(stmt != NULL) delete stmt;}

    virtual void        setStatement    (Statement* statement)          { stmt=statement; }

protected:
            Statement*  stmt;
            bool        topLevel;
};



/*
 * Represents the for-loop
 */
class ForLoop : public Loop {

public:
                        ForLoop         (std::string varName, bool top) : Loop(top), vName(varName) { fromExpr=toExpr=stepExpr=NULL; }
   virtual             ~ForLoop         ();

   virtual  void        execute         ();

   virtual  void        setFrom         (Expression* fromExpression)    { fromExpr=fromExpression; }
   virtual  void        setTo           (Expression* toExpression)      { toExpr=toExpression; }
   virtual  void        setStep         (Expression* stepExpression)    { stepExpr=stepExpression; }

protected:
            std::string vName;

            Expression* fromExpr;
            Expression* toExpr;
            Expression* stepExpr;

private:
                        ForLoop         (const ForLoop& src):Loop(src.topLevel) { } //DISABLED
            ForLoop     operator=       (const ForLoop& src)             { return *this; } //DISABLED
};


/*
 * Abstract aggregate of the very similar conditional loops
 */
class CondLoop : public Loop {

public:
                        CondLoop        (bool top) : Loop(top)          { cond=NULL; }
    virtual            ~CondLoop        ()                              { if(cond!=NULL) delete cond; }
    virtual void        setCond         (Expression* condition)         { cond = condition; }

protected:
            Expression* cond;
};


/*
 * Represents the 'repeat' conditional loop
 */
class RepeatLoop : public CondLoop {

public:
                        RepeatLoop      (bool top) : CondLoop(top)      { }
    virtual void        execute         ();

private:
                        RepeatLoop      (const RepeatLoop& src):CondLoop(src.topLevel) { }  //DISABLED
            RepeatLoop  operator=       (const RepeatLoop& src)         { return *this; } //DISABLED
};


/*
 * Represents the 'while' conditional loop
 */
class WhileLoop : public CondLoop {

public:
                        WhileLoop       (bool top) : CondLoop(top)      { }
    virtual void        execute         ();

private:
                        WhileLoop       (const WhileLoop& src):CondLoop(src.topLevel) { } //DISABLED
            WhileLoop   operator=       (const WhileLoop& src)          { return *this; } //DISABLED
};

#endif	/* _LOOP_H */
