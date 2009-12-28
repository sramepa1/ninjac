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
#include <iomanip>
#include <cmath>

#include "exprstmt.h"
#include "globals.h"

using namespace std;

void ExprStatement::setExpr(Expression* expr) {
    #ifdef DEBUG
        assert(!expression);
        assert(expr);
    #endif

    expression = expr;
}

/*
 * Always evaluates, only prints in interactive mode
 */
void ExpressionStatement::execute() {
    #ifdef DEBUG
        cout << "### executing ExpressionStatement" << endl;
        assert(expression);
    #endif

    double result = expression->evaluate();
    if(Globals::inst->ia()) {
        cout << "#> " << (fabs(result) <= Globals::inst->delta ? 0.0 : result) << endl;
    }

    #ifdef DEBUG
        else cout << "### ExpressionStatement value thrown away: " << result << endl;
    #endif
}

/*
 * Always prints
 */
void PrintStatement::execute() {
    #ifdef DEBUG
        cout << "### executing PrintStatement" << endl;
        assert(expression);
    #endif

    double result = expression->evaluate();
    cout << "#> " << (fabs(result) <= Globals::inst->delta ? 0.0 : result) << endl;
}

/*
 * Takes any value, but:
 * - trims sign
 * - rounds to integer
 * - caps maximum at 16 (more decimal digits are outside double's precision)
 */
void PrecisionStatement::execute() {
    #ifdef DEBUG
        cout << "### executing PrecisionStatement" << endl;
        assert(expression);
    #endif

    double tmp = round(fabs(expression->evaluate()));
    int result = tmp > 16.0 ? 16 : (int)tmp;

    if(Globals::inst->ia()) {
        cout << "#> " << "Display precision set to " << result << " digits." << endl;
    }

    #ifdef DEBUG
    else cout << "### Display precision set to " << result << " digits." << endl;
    // for script mode
    #endif

    cout << setprecision(result);
}
