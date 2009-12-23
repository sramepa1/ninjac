#include <string>

#include "parser.h"
#include "globals.h"
#include "interpreter.h"

#ifdef DEBUG
    #include <iostream>
#endif

using namespace std;

Parser::Parser() {
    keywords.insert("begin");
    keywords.insert("end");

    keywords.insert("if");
    keywords.insert("then");
    keywords.insert("else");

    keywords.insert("while");
    keywords.insert("do");

    keywords.insert("repeat");
    keywords.insert("until");

    keywords.insert("for");
    keywords.insert("from");
    keywords.insert("to");
    keywords.insert("step");

    keywords.insert("function");
    keywords.insert("of");
    keywords.insert("is");
    keywords.insert("return");

    keywords.insert("precision");

    keywords.insert("print");
}


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

    FunctionCall* fc1 = new FunctionCall("sqrt",42,42);
    fc1->addValue(new Constant(9));
    ExpressionStatement* es3 = new ExpressionStatement();
    es3->setExpr(fc1);

    Globals::inst->getProg()->append(es3);

    if(Globals::inst->getFuncs()->find("trikratvynasob") == Globals::inst->getFuncs()->end()) {
        FunctionDeclaration* fd1 = new FunctionDeclaration("trikratvynasob");
        fd1->addArgument("prvni");
        fd1->addArgument("druhy");
        ForLoop* for1 = new ForLoop("i");
        for1->setFrom(new Constant(1));
        for1->setTo(new Constant(3));
        for1->setStep(new Constant(1));
        Assignment* ass2 = new Assignment("prvni");
        Operator* mulOper = new MulOperator();
        mulOper->setLeft(new Variable("prvni"));
        mulOper->setRight(new Variable("druhy"));
        ass2->setValue(mulOper);
        for1->setStatement(ass2);
        fd1->setBody(for1);
        fd1->setReturn(new Variable("prvni"));

        Globals::inst->getProg()->append(fd1);
    }
    
    FunctionCall* fc2 = new FunctionCall("trikratvynasob",42,42);
    fc2->addValue(new Variable("testVar"));
    fc2->addValue(new Constant(42));
    ExpressionStatement* es4 = new ExpressionStatement();
    es4->setExpr(fc2);

    Globals::inst->getProg()->append(es4);
    
    if(source.compare("exit") == 0) {
        Globals::inst->getProg()->append(new ExitStatement());
    }
    
}
