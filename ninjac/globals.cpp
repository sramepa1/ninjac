#ifdef DEBUG
    #include <iostream>
#endif

#include "globals.h"
#include "parser.h"
#include "block.h"

using namespace std;

Globals::Globals() {
    interactive = true;
    parser = new Parser();
    program = new Block();
    delta = 1e-12;
    globalVars = new map<string,double>();
    localVarStack = new stack<map<string,double>*>();
}

Globals::~Globals() {
    delete parser;
    delete program;
    delete globalVars;
    delete localVarStack;
}

void Globals::resetProg() {
    #ifdef DEBUG
        cout << "### -- resetting program block --" << endl;
    #endif

    delete program;
    program = new Block();
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

Globals* const Globals::inst = new Globals();
