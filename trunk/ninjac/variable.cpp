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
    #include <iostream>
    #include <assert.h>
#endif

#include "variable.h"
#include "globals.h"

using namespace std;

/*
 * The algorithm for determining the value of a variable:
 * - no function context -> look in global variables
 * - function context -> first look in local, if not found -> look in global
 * - not found (uninitialized variable) -> return 0
 */
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
