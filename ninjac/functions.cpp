#ifdef DEBUG
    #include <cassert>
    #include <iostream>
#endif

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
    
    function = NULL;
}

void FunctionDeclaration::addArgument(std::string arg) {
    #ifdef DEBUG
        assert(function);
    #endif

    function->args.push_back(arg);
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




double FunctionCall::evaluate() const {
    #ifdef DEBUG
        cout << "### calling function " << name << endl;
    #endif

    if(Globals::inst->getFuncs()->find(name) == Globals::inst->getFuncs()->end()) {
        throw NinjacException(true,(string("unknown function: ")+name).c_str(),line,column);
    }

    func* fn = (*Globals::inst->getFuncs())[name];
    unsigned int expArgs = fn->args.size();
    if(expArgs != values.size()) {
        ostringstream os;
        os << "argument count mismatch - expected " << expArgs << ", found " << values.size();
        throw NinjacException(true,os.str().c_str(),line,column);
    }

    #ifdef DEBUG
        assert(fn->retExpr);
        cout << "### function " << name << " exists, arg count OK - evaluating arg values" << endl;
    #endif

    map<string,double>* argmap = new map<string,double>();
    try {
        for(unsigned int i = 0; i < values.size(); i++) {
            (*argmap)[fn->args[i]] = values[i]->evaluate();
        }
    }catch(NinjacException e) {

        #ifdef DEBUG
            cout << "### EXCEPTION when evaluating args of func " << name << " - deleting map, rethrowing" << endl;
        #endif

        delete argmap;
        throw e;
    }
    Globals::inst->getLocalVars()->push(argmap);

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

    Globals::inst->getLocalVars()->pop();
    delete argmap;

    if(isnan(result) || isinf(result) || isinf(-result)) {
        throw NinjacException(true,"argument(s) were outside function's domain",line,column);
    }

    return result;
}

FunctionCall::~FunctionCall() {
    for (unsigned int i = 0; i < values.size(); i++) {
        delete values[i];
    }
}
