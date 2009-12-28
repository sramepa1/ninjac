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
#ifdef DEBUG    
    #include <assert.h>    
#endif

#include <iostream>
#include <cmath>

#include "loops.h"
#include "globals.h"

using namespace std;

ForLoop::~ForLoop() {
    if(fromExpr != NULL) delete fromExpr;
    if(toExpr != NULL) delete toExpr;
    if(stepExpr != NULL) delete stepExpr;
}

/*
 * executes a for-loop. Algorithm is:
 * - evaluate bounds and step
 * - determine direction
 * - repeat execution and control var assignment until second bound is stepped over
 */
void ForLoop::execute() {
    #ifdef DEBUG
        cout << "### entering for loop, evaluating expressions" << endl;
        assert(fromExpr);
        assert(toExpr);
        assert(stepExpr);
    #endif

    double from = fromExpr->evaluate();
    double to = toExpr->evaluate();
    double step = fabs(stepExpr->evaluate()); // strips sign
    bool up = to >= from;

    #ifdef DEBUG
        cout << "### for loop control var name: " << vName << endl
             << "###   from=" << from << " to=" << to << " step=" << step << endl;
    #endif

    double varValue = from;
    while(  (up && (varValue <= to + Globals::inst->delta))
          || (!up && (varValue >= to - Globals::inst->delta))) {

        #ifdef DEBUG
            cout << "### executing an iteration of for loop, $" << vName << " is " << varValue << ',' << endl
                 << "###   iteration is from " << from << " to " << to << " step " << step << endl;
        #endif

        Globals::inst->assignVar(vName,varValue);
        stmt->execute();
        varValue = up ? varValue + step : varValue - step;
    }

    if((varValue == from)) { // unchanged
        Globals::inst->assignVar(vName,from);
    }

    if(Globals::inst->ia() && topLevel) {
        cout << "#> OK" << endl;
    }

    #ifdef DEBUG
        cout << "### leaving for loop, $" << vName << '=' << Variable(vName).evaluate() << " ( " << (up?">= ":"<= ") << to << " )" << endl;
    #endif
}


/*
 * repeats body execution until condition is true
 */
void RepeatLoop::execute() {
    #ifdef DEBUG
        cout << "### entering repeat loop" << endl;
    #endif

    do {
        #ifdef DEBUG
            cout << "### executing an iteration of repeat loop" << endl;
        #endif

        stmt->execute();

    }while (fabs(cond->evaluate()) <= Globals::inst->delta);

    if(Globals::inst->ia() && topLevel) {
        cout << "#> OK" << endl;
    }

    #ifdef DEBUG
        cout << "### leaving repeat loop" << endl;
    #endif
}


/*
 * while condition is true, repeats body execution
 */
void WhileLoop::execute() {
    #ifdef DEBUG
        cout << "### entering while loop" << endl;
    #endif

    while (fabs(cond->evaluate()) > Globals::inst->delta) {

        #ifdef DEBUG
            cout << "### executing an iteration of while loop" << endl;
        #endif

        stmt->execute();
    }

    if(Globals::inst->ia() && topLevel) {
        cout << "#> OK" << endl;
    }

    #ifdef DEBUG
        cout << "### leaving while loop" << endl;
    #endif
}
