#include <sstream>
#include <stack>

#include "parser.h"
#include "globals.h"
#include "interpreter.h"
#include "ninjacexcept.h"

#ifdef DEBUG
    #include <cassert>
#endif

using namespace std;

Parser::Parser() {
    tok = new Tokenizer(this);

    reset();

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

    oneCharOper = "+-*/\\%&|=<>";

    twoCharOper.insert("==");
    twoCharOper.insert("<>");
    twoCharOper.insert("&&");
    twoCharOper.insert("||");
    twoCharOper.insert("<=");
    twoCharOper.insert(">=");
}

Parser::~Parser() {
    delete tok;
}

void Parser::reset() {
    line = 1; column = 1;
    tok->reset();
}

void Parser::parse(istream& is) {

    #ifdef DEBUG
        cout << "### Commencing parsing" << endl;
    #endif

    is >> noskipws;

    ExpressionStatement* dummy = new ExpressionStatement();
    dummy->setExpr(parseExpr(is));
    Globals::inst->getProg()->append(dummy);

    tok->tokenOK();

    /* !!!!! =========== DUMMY PARSER =========== !!!!!

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
    */
    #ifdef DEBUG
        cout << "### Parsing completed" << endl;
    #endif
}

Expression* Parser::parseExpr(istream& is) {
    #ifdef DEBUG
        cout << "### Parsing expression" << endl;
    #endif

    // shunting-yard algorithm: infix -> RPN queue
    queue<Token*> out;
    shuntingYard(is,out);

    #ifdef DEBUG
        cout << "### Parsing tree from RPN, queue length: " << out.size() << endl;
    #endif

    // RPN queue -> interpretation tree
    stack<Expression*> stack;
    std::stack<Expression*> tmpStack;
    istringstream sin;
    do {
        Token* t = out.front();
        out.pop();
        #ifdef DEBUG
            cout << "### parsing token: " << t->value << " (length " << t->value.length() << ") of type " << t->type << endl;
            assert(t->value.length());
        #endif
        switch(t->type) {
            case Token::NUM:
                                sin.clear();
                                sin.str(t->value);
                                double d;
                                sin >> d;
                                #ifdef DEBUG
                                    cout << "### parsed: " << d << endl;
                                    assert(!sin.fail());
                                #endif
                                stack.push(new Constant(d));
                                break;
            case Token::VAR:
                                stack.push(new Variable(t->value));
                                break;
            case Token::OPER:
                                Operator* op = getOperator(t->value,t->l,t->c);
                                if(stack.size() < 2) {
                                    delete op;
                                    throw NinjacException(false,"not enough operands for operator",t->l,t->c);
                                }
                                op->setRight(stack.top());
                                stack.pop();
                                op->setLeft(stack.top());
                                stack.pop();
                                stack.push(op);
                                break;
            case Token::FUNC:
                                FunctionCall* fc = new FunctionCall(t->value,t->l,t->c);
                                #ifdef DEBUG
                                    cout << "### Parsing function " << t->value << ", argc = " << t->argc << endl;
                                #endif
                                if(stack.size() < t->argc) {
                                    delete fc;
                                    throw NinjacException(false,"missing argument(s)",t->l,t->c);
                                }
                                for (unsigned int i = 0; i < t->argc; i++) {
                                    tmpStack.push(stack.top());
                                    stack.pop();
                                }
                                while(!tmpStack.empty()){
                                    fc->addValue(tmpStack.top());
                                    tmpStack.pop();
                                }
                                stack.push(fc);
                                break;
        }
    }while(!out.empty());

    #ifdef DEBUG
    assert(!stack.empty());
    #endif
    if(stack.size() > 1) {
        throw NinjacException(false,"not an expression (near here)", line, column);
    }

    return stack.top();
}

Statement* Parser::parseStmt(istream& is) {
    return NULL;
}

void Parser::shuntingYard(istream& is, queue<Token*>& out) {
    std::stack<Token*> stack;
    std::stack<int> argCntStack;

    bool end = false;

    do {
        Token* t = tok->getToken(is,line,column); // TODO catch!
        #ifdef DEBUG
            cout << "### received token: " << t->value << " (length " << t->value.length() << ") of type " << t->type << endl;
        #endif

        switch(t->type) {
            case Token::NUM :   //fall-through
            case Token::VAR :
                                out.push(t);
                                tok->tokenOK();
                                break;
            case Token::FUNC:   argCntStack.push(0); //fall-through;
            case Token::LEFT_P:
                                stack.push(t);
                                tok->tokenOK();
                                break;
            case Token::RIGHT_P:
                                while (!stack.empty() && stack.top()->type != Token::LEFT_P){
                                    out.push(stack.top());
                                    stack.pop();
                                }
                                if(stack.empty()) {
                                    throw NinjacException(false,"unmatched parthenses near this location",t->l,t->c);
                                }
                                #ifdef DEBUG
                                    assert(stack.top()->type == Token::LEFT_P);
                                #endif
                                stack.pop();
                                if(!stack.empty() && stack.top()->type == Token::FUNC) {
                                    Token* f = stack.top();
                                    f->argc = argCntStack.top() + 1;
                                    argCntStack.pop();
                                    out.push(f);
                                    stack.pop();
                                }
                                tok->tokenOK();
                                break;
            case Token::OPER:
                                while(!stack.empty() && ( stack.top()->type == Token::FUNC || (stack.top()->type == Token::OPER && tok->hasLTEpriority(t,stack.top())))){
                                    out.push(stack.top());
                                    stack.pop();
                                }
                                stack.push(t);
                                tok->tokenOK();
                                break;
            case Token::ARG_SEP:
                                while (!stack.empty() && stack.top()->type != Token::LEFT_P){
                                    out.push(stack.top());
                                    stack.pop();
                                }
                                if(stack.empty()) {
                                    throw NinjacException(false,"misplaced argument separator or unmatched parthenses",t->l,t->c);
                                }
                                int tmp = argCntStack.top()+1;
                                argCntStack.pop();
                                argCntStack.push(tmp);
                                tok->tokenOK();
                                break;
            default:
                                end = true;
                                break;
        }
    }while(!end);

    while(!stack.empty()) {
        if(stack.top()->type == Token::LEFT_P) {
            throw NinjacException(false,"unmatched parthenses near this location",stack.top()->l,stack.top()->c);
        }
        out.push(stack.top());
        stack.pop();
    }

    if(out.empty()) throw NinjacException(false,"expected an expression",line,column);
}

Operator* Parser::getOperator(string oper, int l, int c) {
    if(oper == "+") return new PlusOperator();
    if(oper == "-") return new MinusOperator();
    if(oper == "/") return new DivOperator(l,c);
    if(oper == "*") return new MulOperator();
    if(oper == "\\") return new IntDivOperator(l,c);
    if(oper == "%") return new ModuloOperator(l,c);
    if(oper == "<") return new LessOperator();
    if(oper == ">") return new GreaterOperator();
    if(oper == ">=") return new GTEOperator();
    if(oper == "<=") return new LTEOperator();
    if(oper == "<>") return new NotEqualsOperator();
    if(oper == "=" || oper == "==") return new EqualsOperator();
    if(oper == "&" || oper == "&&") return new AndOperator();
    if(oper == "|" || oper == "||") return new OrOperator();

    #ifdef DEBUG
        assert(0);
    #endif
    return NULL;
}
