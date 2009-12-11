#include "exprstmt.h"
#include "globals.h"

#define DEBUG 1

#ifdef DEBUG
    #include <iostream>
    using namespace std;
#endif

void ExpressionStatement::execute() const {
    #ifdef DEBUG
        cout << "### executing ExpressionStatement" << endl;
    #endif

    double result = expression->evaluate();
    if(Globals::inst->ia()) {
        cout << "#> " << result << endl;
    }

    #ifdef DEBUG
        else cout << "### ExpressionStatement value thrown away: " << result << endl;
    #endif
}
