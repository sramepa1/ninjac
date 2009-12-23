#include "exprstmt.h"
#include "globals.h"
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

#ifdef DEBUG
    #include <assert.h>
#endif

void ExprStatement::setExpr(Expression* expr) {
    #ifdef DEBUG
        assert(!expression);
        assert(expr);
    #endif

    expression = expr;
}

void ExpressionStatement::execute() {
    #ifdef DEBUG
        cout << "### executing ExpressionStatement" << endl;
        assert(expression);
    #endif

    double result = expression->evaluate();
    if(Globals::inst->ia()) {
        cout << "#> " << result << endl;
    }

    #ifdef DEBUG
        else cout << "### ExpressionStatement value thrown away: " << result << endl;
    #endif
}

void PrintStatement::execute() {
    #ifdef DEBUG
        cout << "### executing PrintStatement" << endl;
        assert(expression);
    #endif

    cout << "#> " << expression->evaluate() << endl;
}

void PrecisionStatement::execute() {
    #ifdef DEBUG
        cout << "### executing PrecisionStatement" << endl;
        assert(expression);
    #endif

    int result = (int)round(expression->evaluate());
    if(Globals::inst->ia()) {
        cout << "#> " << "Precision set to " << result << " digits." << endl;
    }

    #ifdef DEBUG
        else cout << "### Precision set to " << result << " digits." << endl;
    #endif

    cout << setprecision(result);
}
