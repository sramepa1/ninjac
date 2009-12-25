#ifdef DEBUG
    #include <iostream>
#endif

#include "globals.h"
#include "expression.h"
#include "builtin.h"

using namespace std;

Globals::Globals() {
    interactive = true;
    parser = new Parser();
    program = new Block();
    delta = 1e-12;
    globalVars = new map<string,double>();
    localVarStack = new stack<map<string,double>*>();
    functions = new map<string,func*>();

    initBuiltIn();
}

Globals::~Globals() {
    delete parser;
    delete program;
    delete globalVars;
    while(!localVarStack->empty()) {
        map<string,double>* tmp = localVarStack->top();
        localVarStack->pop();
        delete tmp;
    }
    delete localVarStack;
    for(map<string,func*>::iterator i = functions->begin(); i != functions->end(); ++i) {
        delete (*i).second;
    }
    delete functions;
}

void Globals::resetProg() {
    #ifdef DEBUG
        cout << "### -- resetting program block --" << endl;
    #endif

    delete program;
    program = new Block();
    parser->reset();
}

void Globals::assignVar(string varName, double value) {

    if(getLocalVars()->empty() || (getVars()->count(varName) == 1) ) {
        #ifdef DEBUG
            cout << "### assigned global variable $" << varName;
        #endif

        (*globalVars)[varName] = value;

    }else {
        #ifdef DEBUG
            cout << "### assigned local variable $" << varName;
            assert(globalVars->count(varName) == 0);
        #endif

        (*(localVarStack->top()))[varName] = value;
    }

    #ifdef DEBUG
        cout << " a value of " << value << endl;
    #endif
}

void Globals::initBuiltIn() {
    func* temp;

    temp = new func;
    temp->body = NULL;
    temp->retExpr = new BuiltInPi();
    (*functions)["pi"] = temp;

    temp = new func;
    temp->body = NULL;
    temp->retExpr = new BuiltInE();
    (*functions)["e"] = temp;



    temp = new func;
    temp->args.push_back("firstarg");
    temp->body = NULL;
    temp->retExpr = new BuiltInNot();
    (*functions)["not"] = temp;

    temp = new func;
    temp->args.push_back("firstarg");
    temp->body = NULL;
    temp->retExpr = new BuiltInSqrt();
    (*functions)["sqrt"] = temp;

    temp = new func;
    temp->args.push_back("firstarg");
    temp->body = NULL;
    temp->retExpr = new BuiltInAbs();
    (*functions)["abs"] = temp;

    temp = new func;
    temp->args.push_back("firstarg");
    temp->body = NULL;
    temp->retExpr = new BuiltInRound();
    (*functions)["round"] = temp;

    temp = new func;
    temp->args.push_back("firstarg");
    temp->body = NULL;
    temp->retExpr = new BuiltInSin();
    (*functions)["sin"] = temp;

    temp = new func;
    temp->args.push_back("firstarg");
    temp->body = NULL;
    temp->retExpr = new BuiltInCos();
    (*functions)["cos"] = temp;

    temp = new func;
    temp->args.push_back("firstarg");
    temp->body = NULL;
    temp->retExpr = new BuiltInTan();
    (*functions)["tan"] = temp;

    temp = new func;
    temp->args.push_back("firstarg");
    temp->body = NULL;
    temp->retExpr = new BuiltInASin();
    (*functions)["asin"] = temp;

    temp = new func;
    temp->args.push_back("firstarg");
    temp->body = NULL;
    temp->retExpr = new BuiltInACos();
    (*functions)["acos"] = temp;

    temp = new func;
    temp->args.push_back("firstarg");
    temp->body = NULL;
    temp->retExpr = new BuiltInATan();
    (*functions)["atan"] = temp;

    temp = new func;
    temp->args.push_back("firstarg");
    temp->body = NULL;
    temp->retExpr = new BuiltInLog();
    (*functions)["log"] = temp;

    temp = new func;
    temp->args.push_back("firstarg");
    temp->body = NULL;
    temp->retExpr = new BuiltInLn();
    (*functions)["ln"] = temp;

    temp = new func;
    temp->args.push_back("firstarg");
    temp->body = NULL;
    temp->retExpr = new BuiltInExp();
    (*functions)["exp"] = temp;

    temp = new func;
    temp->args.push_back("firstarg");
    temp->body = NULL;
    temp->retExpr = new BuiltInSgn();
    (*functions)["sgn"] = temp;



    temp = new func;
    temp->args.push_back("firstarg");
    temp->args.push_back("secondarg");
    temp->body = NULL;
    temp->retExpr = new BuiltInPow();
    (*functions)["pow"] = temp;

    temp = new func;
    temp->args.push_back("firstarg");
    temp->args.push_back("secondarg");
    temp->body = NULL;
    temp->retExpr = new BuiltInMax();
    (*functions)["max"] = temp;

    temp = new func;
    temp->args.push_back("firstarg");
    temp->args.push_back("secondarg");
    temp->body = NULL;
    temp->retExpr = new BuiltInMin();
    (*functions)["min"] = temp;
}

Globals* const Globals::inst = new Globals();
