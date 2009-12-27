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

void ForLoop::execute() {
    #ifdef DEBUG
        cout << "### entering for loop, evaluating expressions" << endl;
        assert(fromExpr);
        assert(toExpr);
        assert(stepExpr);
    #endif

    double from = fromExpr->evaluate();
    double to = toExpr->evaluate();
    double step = fabs(stepExpr->evaluate());
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