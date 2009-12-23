#include "exprstmt.h"
#include "globals.h"
#include <iostream>
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
