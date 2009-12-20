#ifdef DEBUG
    #include <iostream>
    #include <assert.h>
#endif

#include "variable.h"
#include "globals.h"

using namespace std;

double Variable::evaluate() const {
    #ifdef DEBUG
        cout << "### evaluating value of variable $" << n << endl;
    #endif

    if(Globals::inst->getLocalVars()->empty()) {
        #ifdef DEBUG
            cout << "### looking for $" << n << " in global variables" << endl;
        #endif

        if (Globals::inst->getVars()->count(n) > 0 ) {
            #ifdef DEBUG
                cout << "###  $" << n << " found in global variables, value is "
                        << Globals::inst->getVars()->find(n)->second << endl;
                assert(Globals::inst->getVars()->count(n) == 1);
            #endif

            return Globals::inst->getVars()->find(n)->second;

        } else {
            #ifdef DEBUG
                cout << "###  $" << n << " not found, returning 0.0" << endl;
                assert(Globals::inst->getVars()->count(n) == 0);
            #endif

            return 0.0;
        }
    }else {
        #ifdef DEBUG
            cout << "### looking for $" << n << " in local variables" << endl;
        #endif

        if (Globals::inst->getLocalVars()->top()->count(n) > 0 ) {
            #ifdef DEBUG
                cout << "###  $" << n << " found in local variables, value is "
                        << Globals::inst->getLocalVars()->top()->find(n)->second << endl;
                assert(Globals::inst->getLocalVars()->top()->count(n) == 1);
            #endif

            return Globals::inst->getLocalVars()->top()->find(n)->second;

        }else if (Globals::inst->getVars()->count(n) > 0 ) {
            #ifdef DEBUG
                cout << "###  $" << n << " found in global variables, value is "
                        << Globals::inst->getVars()->find(n)->second << endl;
                assert(Globals::inst->getVars()->count(n) == 1);
            #endif

            return Globals::inst->getVars()->find(n)->second;

        } else {
            #ifdef DEBUG
                cout << "###  $" << n << " not found, returning 0.0" << endl;
                assert(Globals::inst->getLocalVars()->top()->count(n) == 0);
            #endif

            return 0.0;
        }
    }
}
