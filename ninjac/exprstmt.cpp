#include "exprstmt.h"
#include "globals.h"
#include <iostream>
using namespace std;

#ifdef DEBUG
    #include <assert.h>
#endif

void ExpressionStatement::execute() const {
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

void ExpressionStatement::setExpr(Expression* expr) {
    #ifdef DEBUG
        assert(!expression);
        assert(expr);
    #endif
        
    expression = expr;
}
