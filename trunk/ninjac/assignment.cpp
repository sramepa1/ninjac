#ifdef DEBUG
    #include <iostream>
    #include <assert.h>
#endif

#include "assignment.h"
#include "globals.h"

using namespace std;

void Assignment::execute() const {
    #ifdef DEBUG
        cout << "### explicit assignment to variable $" << vName << " - evaluating new value first" << endl;
        assert(val);
    #endif

    Globals::inst->assignVar(vName, val->evaluate());
}

void Assignment::setValue(Expression* value) {
    #ifdef DEBUG
        assert(!val);
    #endif

    val = value;
}
