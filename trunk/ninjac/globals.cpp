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
    delete program;
    program = new Block();
}

Globals* const Globals::inst = new Globals();
