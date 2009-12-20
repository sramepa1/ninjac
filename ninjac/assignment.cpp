#ifdef DEBUG
    #include <iostream>
    #include <assert.h>
#endif

#include "assignment.h"
#include "globals.h"

using namespace std;

void Assignment::execute() const {
    #ifdef DEBUG
        cout << "### assigning to variable $" << vName << " - evaluating new value first" << endl;
        assert(val);
    #endif

    double value = val->evaluate();

    if(Globals::inst->getLocalVars()->empty() || (Globals::inst->getVars()->count(vName) == 1) ) {
        #ifdef DEBUG
            cout << "### assigned global variable $" << vName;
        #endif

        (*(Globals::inst->getVars()))[vName] = value;

    }else {
        #ifdef DEBUG
            cout << "### assigned local variable $" << vName;
            assert(Globals::inst->getVars()->count(vName) == 0);
        #endif

        (*(Globals::inst->getLocalVars()->top()))[vName] = value;
    }

    #ifdef DEBUG
        cout << " a value of " << value << endl;
    #endif
}
