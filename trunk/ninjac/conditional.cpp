#include <cmath>

#include "conditional.h"
#include "expression.h"
#include "globals.h"

#ifdef DEBUG
    #include <iostream>
    #include <assert.h>
    using namespace std;
#endif

Conditional::~Conditional() {
    if(cond != NULL) delete cond;
    if(ifTrue != NULL) delete ifTrue;
    if(ifFalse != NULL) delete ifFalse;
}

void Conditional::execute() const {
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

    } else if(ifFalse != NULL) {
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
}
