#ifdef DEBUG
    #include <iostream>
    #include <assert.h>
#endif

#include "assignment.h"
#include "globals.h"

using namespace std;

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
