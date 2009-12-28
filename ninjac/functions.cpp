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
#endif

#include <iostream>
#include <sstream>
#include <cmath>

#include "functions.h"
#include "globals.h"
#include "variable.h"
#include "ninjacexcept.h"

using namespace std;


func::~func() {
    if(body != NULL) delete body;
    if(retExpr != NULL) delete retExpr;
}



FunctionDeclaration::FunctionDeclaration(std::string funcName) : name(funcName) {
    function = new func;
    function->body = NULL;
    function->retExpr = NULL;
}

void FunctionDeclaration::execute() {
    #ifdef DEBUG
        assert(Globals::inst->getFuncs()->find(name) == Globals::inst->getFuncs()->end());
        assert(function);
        assert(function->retExpr);
    #endif

    (*(Globals::inst->getFuncs()))[name] = function;

    if(Globals::inst->ia()) {
        cout << "#> Function " << name << " of " << function->args.size() << " arguments successfully declared." << endl;
    }
    
    function = NULL; // FunctionDeclaration only executes once - ownership of function is transferred to the map in Globals
                     // The parser guarantees it to be a top level statement, and not to redefine an existing function
}

void FunctionDeclaration::addArgument(std::string arg) {
    #ifdef DEBUG
        assert(function);
    #endif
        
    function->args.push_back(arg);
}

bool FunctionDeclaration::hasArgument(std::string arg) {
    #ifdef DEBUG
        assert(function);
    #endif

    for(vector<string>::iterator i = function->args.begin(); i != function->args.end(); ++i) {
        if(*i == arg) return true;
    }
    return false;
}

void FunctionDeclaration::setBody(Statement* body) {
    #ifdef DEBUG
        assert(function);
        assert(!function->body);
    #endif

    function->body = body;
}

void FunctionDeclaration::setReturn(Expression* expr) {
    #ifdef DEBUG
        assert(function);
    #endif

    function->retExpr = expr;
}



/*
 * Evaluates a function call.
 * Function existence and argument count match is tested at runtime
 * to allow recursive functions to be declared without C-like headers.
 *
 * Algorithm is:
 * - perform runtime checks
 * - evaluate arguments
 * - push local vars to stack
 * - execute body
 * - evaluate return
 * - pop local vars from stack
 * - actually return something
 */
double FunctionCall::evaluate() const {
    #ifdef DEBUG
        cout << "### calling function " << name << endl;
    #endif

    if(Globals::inst->getFuncs()->find(name) == Globals::inst->getFuncs()->end()) { //existence test
        throw NinjacException(true,(string("unknown function: ")+name).c_str(),line);
    }

    func* fn = (*Globals::inst->getFuncs())[name];
    unsigned int expArgs = fn->args.size();
    if(expArgs != values.size()) {              // argument count test
        ostringstream os;
        os << "argument count mismatch - expected " << expArgs << ", found " << values.size();
        throw NinjacException(true,os.str().c_str(),line);
    }

    if(Globals::inst->getLocalVars()->size() >= 1000) { // stack overflow test. System stack overflows at about 3500 calls.
        throw NinjacException(true,"stack overflow",line);
    }

    #ifdef DEBUG
        assert(fn->retExpr);
        cout << "### function " << name << " exists, arg count OK - evaluating arg values" << endl;
    #endif

    map<string,double>* argmap = new map<string,double>(); //create local variable map
    try {
        for(unsigned int i = 0; i < values.size(); i++) {   //fill it with arguments and their values
            (*argmap)[fn->args[i]] = values[i]->evaluate();
        }
    }catch(NinjacException e) {

        #ifdef DEBUG
            cout << "### EXCEPTION when evaluating args of func " << name << " - deleting map, rethrowing" << endl;
        #endif

        delete argmap;
        throw e;
    }
    Globals::inst->getLocalVars()->push(argmap);    // push map to stack

    #ifdef DEBUG
        cout << "### all args of function " << name << " evaluated, " << (fn->body == NULL ? "no body to execute" : "executing body") << endl;
    #endif

    if(fn->body != NULL) fn->body->execute();

    #ifdef DEBUG
        cout << "### " << (fn->body == NULL ? "" : "body executed, ") << "evaluating return value of function " << name << endl;
    #endif

    double result = fn->retExpr->evaluate();

    #ifdef DEBUG
        cout << "### return value of function " << name << " evaluated to " << result << endl;
    #endif

    Globals::inst->getLocalVars()->pop();   // finished execution - pop map
    delete argmap;

    if(isnan(result) || isnan(result + (-result))) { // NaN or infinity test (needed for built-ins)
        throw NinjacException(true,"argument(s) outside function's domain",line);
    }

    return result;
}

FunctionCall::~FunctionCall() {
    for (unsigned int i = 0; i < values.size(); i++) {
        delete values[i];
    }
}
