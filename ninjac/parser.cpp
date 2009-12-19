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
        cout << "### Input to parse -------------------------" << endl;
        cout << "### " << source << endl;
        cout << "### End of input ---------------------------" << endl;
    #endif

    // !!!!! =========== DUMMY PARSER =========== !!!!!
    Globals::inst->getProg()->append(new ExpressionStatement(new Constant(42)));
    
}
