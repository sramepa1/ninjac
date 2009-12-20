#include <string>

#include "parser.h"
#include "globals.h"
#include "interpreter.h"

#ifdef DEBUG
    #include <iostream>
#endif

using namespace std;

void Parser::parse(std::string& source) {

    #ifdef DEBUG
        cout << "### --- Input to parse -------------------------" << endl;
        cout << "### " << source << endl;
        cout << "### --- End of input ---------------------------" << endl;
    #endif

    // !!!!! =========== DUMMY PARSER =========== !!!!!
    Expression* c1 = new Constant(42);
    ExpressionStatement* es1 = new ExpressionStatement();
    es1->setExpr(c1);
    Globals::inst->getProg()->append(es1);
    
}
