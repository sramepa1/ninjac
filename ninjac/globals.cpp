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
    #include <cassert>
    #include <iostream>
#endif

#include <cstdlib>
#include <ctime>

#include "globals.h"
#include "expression.h"
#include "builtins.h"

using namespace std;

/*
 * initializes the support fields
 */
Globals::Globals() {
    interactive = true; // will be overwritten by main(), but I'd rather not leave it uninitialized
    parser = new Parser();
    program = new Block(false); // false = silent in interactive mode, although it technically *is* a top level statement
    delta = 1e-12;
    globalVars = new map<string,double>();
    localVarStack = new stack<map<string,double>*>();
    functions = new map<string,func*>();

    initBuiltIn(); // fill function map with built-ins
}

/*
 * Does not really need a comment...
 */
Globals::~Globals() {
    delete parser;
    delete program;
    delete globalVars;
    while(!localVarStack->empty()) {
        delete localVarStack->top();
        localVarStack->pop();
    }
    delete localVarStack;
    for(map<string,func*>::iterator i = functions->begin(); i != functions->end(); ++i) {
        delete (*i).second;
    }
    delete functions;
}

/*
 * Purges the program block and any remaining local variables
 * and resets parser state - called between lines in interactive mode
 */
void Globals::resetProg() {
    #ifdef DEBUG
        cout << "### resetting program block" << endl;
    #endif

    delete program;
    program = new Block(false);

    while(!localVarStack->empty()) {
        delete localVarStack->top();
        localVarStack->pop();
    }

    parser->reset();
}

/*
 * Function name says it all. The algorithm for assignment is:
 *
 * no function context -> global
 * in function and this local var already exists -> local
 * in function and this var only exists in global -> global
 * in function and var does not exist at all -> new local
 */
void Globals::assignVar(string varName, double value) {

    if(getLocalVars()->empty() || (getVars()->count(varName) == 1 && getLocalVars()->top()->count(varName) == 0) ) {
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

/*
 * Boring but necessary - pre-fills the function map with the built-in functions
 * from builtins.h
 */
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
    temp->body = NULL;
    temp->retExpr = new BuiltInRand();
    (*functions)["rand"] = temp;

    srand(time(NULL));          // seed and randomize the cstdlib generator
    rand(); rand(); rand();



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

Globals* const Globals::inst = new Globals(); // and don't forget actually instantiating the singleton
