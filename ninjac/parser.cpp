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

    ExpressionStatement* es1 = new ExpressionStatement();
    es1->setExpr(new Constant(42));
    Globals::inst->getProg()->append(es1);
    
    Operator* plus1 = new PlusOperator();
    plus1->setLeft(new Constant(1));
    plus1->setRight(new Variable("testVar"));
    
    Operator* min1 = new MinusOperator();
    min1->setLeft(new Constant(13));
    min1->setRight(plus1);

    Assignment* ass1 = new Assignment("testVar");
    ass1->setValue(min1);

    Globals::inst->getProg()->append(ass1);

    Operator* eq1 = new EqualsOperator();
    eq1->setLeft(new Variable("testVar"));
    eq1->setRight(new Constant(12));

    ExpressionStatement* es2 = new ExpressionStatement();
    es2->setExpr(new Variable("testVar"));

    Conditional* if1 = new Conditional();
    if1->setCondition(eq1);
    if1->setIfTrue(es2);

    Globals::inst->getProg()->append(if1);
    
    if(source.compare("exit") == 0) {
        Globals::inst->getProg()->append(new ExitStatement());
    }
    
}
