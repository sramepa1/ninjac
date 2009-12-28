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

#include "assignment.h"
#include "globals.h"

using namespace std;

// this code does not really need any comments

void Assignment::execute() {
    #ifdef DEBUG
        cout << "### explicit assignment to variable $" << vName << " - evaluating new value first" << endl;
        assert(val);
    #endif

    double newVal = val->evaluate();
    Globals::inst->assignVar(vName, newVal);

    if(Globals::inst->ia() && topLevel) {
        cout << "#> Variable $" << vName << " is now " << newVal << endl;
    }
}

void Assignment::setValue(Expression* value) {
    #ifdef DEBUG
        assert(!val);
    #endif

    val = value;
}
