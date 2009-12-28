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

#include <cmath>
#include <iostream>

#include "conditional.h"
#include "expression.h"
#include "globals.h"

using namespace std;



// this code does not really need any comments

Conditional::~Conditional() {
    if(cond != NULL) delete cond;
    if(ifTrue != NULL) delete ifTrue;
    if(ifFalse != NULL) delete ifFalse;
}

void Conditional::execute() {
    #ifdef DEBUG
        cout << "### executing conditional branch" << endl;
        assert(cond);
        assert(ifTrue);
    #endif

    if(fabs(cond->evaluate()) > Globals::inst->delta) {
        #ifdef DEBUG
            cout << "### condition evaluated to true - executing primary path" << endl;
        #endif

        ifTrue->execute();

    }else if(ifFalse != NULL) {
        #ifdef DEBUG
            cout << "### condition evaluated to false - executing alternate path" << endl;
        #endif

        ifFalse->execute();

    }

    #ifdef DEBUG
    else {
        cout << "### condition evaluated to false and there is no alternate path" << endl;
    }
    #endif

    if(Globals::inst->ia() && topLevel) {
        cout << "#> OK" << endl;
    }
}
