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

#include <sstream>

#include "parser.h"
#include "globals.h"
#include "interpreter.h"
#include "ninjacexcept.h"

using namespace std;

/*
 * Just a boring initialization
 */
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

    keywords.insert("set");

    keywords.insert("exit");

    oneCharOper = "+-*/\\%&|=<>";

    twoCharOper.insert("==");
    twoCharOper.insert("<>");
    twoCharOper.insert("&&");
    twoCharOper.insert("||");
    twoCharOper.insert("<=");
    twoCharOper.insert(">=");
}

/*
 * ...
 */
Parser::~Parser() {
    delete tok;
}

/*
 * Resets parser state, including its Tokenizer
 */
void Parser::reset() {
    topLevel = true;
    line = 1;
    tok->reset();
}

/*
 * Root method of the parsing recursion (this is a recursive-descent parser)
 * Tries to parse the entire content of the given stream, saving output in Globals::program
 */
void Parser::parse(istream& is) {
    #ifdef DEBUG
        cout << "### --- Commencing parsing ---" << endl;
    #endif

    is >> noskipws; // I'll handle whitespace myself (need to count newlines)
    Token* t = tok->getToken(is,line);

    if(t->type == Token::END) {
        cout << "#> What am I supposed to do with empty input?!" << endl;
        return;
    }

    for(;;) { // parse top-level statements, separated by separators
        Globals::inst->getProg()->append(parseStmt(is));
        t = tok->getToken(is,line);
        if(t->type == Token::END) break;
        if(t->type != Token::STMT_SEP) {
            throw NinjacException(false,"expected ';'",t->l);
        }
        delete t;
        tok->tokenOK();
        topLevel = true; // reset the flag - the next statement will be a top-level one
    }
    
    #ifdef DEBUG
        cout << "### --- Parsing completed ---" << endl;
    #endif
}

/*
 * Called when a statement (any kind) is expected.
 * Returns a pointer to a complete Statement object ready for interpretation
 *
 * Takes advantage of the simple grammar - a statement either begins with a keyword
 * or it is an expression-statement.
 */
Statement* Parser::parseStmt(istream& is) {
    #ifdef DEBUG
        cout << "### Parsing statement" << endl;
    #endif

    Token* t = tok->getToken(is,line);

    switch(t->type) {
        case Token::KEYWORD:
                            return parseKeyword(is);
        case Token::FUNC:
        case Token::LEFT_P:
        case Token::NUM:
        case Token::VAR:
                            {ExpressionStatement* es = new ExpressionStatement();
                            es->setExpr(parseExpr(is));
                            return es;}
        default:
                            throw NinjacException(false,"expected statement",t->l);
    };
}

/*
 * Parses a keyword-beginning statement
 * (acknowledges the token, but delegates actual work to sub-functions)
 */
Statement* Parser::parseKeyword(std::istream& is) {
    #ifdef DEBUG
        cout << "### Parsing a statement beginning with keyword" << endl;
    #endif

    Token* t = tok->getToken(is,line);

    #ifdef DEBUG
        assert(t->type == Token::KEYWORD);
        assert(t->value.size());
    #endif

    if(t->value == "set") {
        tok->tokenOK();
        delete t;
        return parseAssign(is);

    }else if(t->value == "begin") {
        tok->tokenOK();
        delete t;
        return parseBlock(is);

    }else if(t->value == "for") {
        tok->tokenOK();
        delete t;
        return parseFor(is);

    }else if(t->value == "while") {
        tok->tokenOK();
        delete t;        
        return parseWhile(is);

    }else if(t->value == "repeat") {
        tok->tokenOK();
        delete t;
        return parseRepeat(is);

    }else if(t->value == "function") {
        if(!topLevel) {
            throw NinjacException(false,"function declaration must be a top level statement",t->l);
        }
        tok->tokenOK();
        delete t;
        topLevel = false;
        return parseFunc(is);

    }else if(t->value == "if") {
        tok->tokenOK();
        delete t;
        return parseIf(is);

    // the last three ones are so simple they don't need subfunctions - parse'em right away
    }else if(t->value == "print") {
        #ifdef DEBUG
            cout << "### Parsing PrintStatement" << endl;
        #endif
        tok->tokenOK();
        delete t;
        Expression* expr = parseExpr(is);
        PrintStatement* p = new PrintStatement();
        p->setExpr(expr);
        return p;

    }else if(t->value == "precision") {
        #ifdef DEBUG
            cout << "### Parsing PrecisionStatement" << endl;
        #endif
        tok->tokenOK();
        delete t;
        Expression* expr = parseExpr(is);
        PrecisionStatement* p = new PrecisionStatement();
        p->setExpr(expr);
        return p;

    }else if(t->value == "exit") {
        #ifdef DEBUG
            cout << "### Parsing ExitStatement" << endl;
        #endif
        tok->tokenOK();
        delete t;
        return new ExitStatement();

    }else {
        ostringstream sout;
        sout << "unexpected keyword: " << t->value;
        throw NinjacException(false,sout.str().c_str(),t->l);
    }
}

/*
 * Parses an assigmnent statement - expects variable, assignment operator, expression
 */
Statement* Parser::parseAssign(std::istream& is) {
    #ifdef DEBUG
        cout << "### Parsing assignment" << endl;
    #endif
    Assignment* ass = new Assignment(parseVar(is),topLevel);
    try {
        Token* t = tok->getToken(is, line);
        if(t->type != Token::ASSIGN) {
            throw NinjacException(false,"expected assignment operator",t->l);
        }
        delete t;
        tok->tokenOK();
        Expression* expr = parseExpr(is);
        ass->setValue(expr);
    }catch(NinjacException e) {
        delete ass;
        throw e;
    }
    #ifdef DEBUG
        cout << "### parsed" << endl;
    #endif
    return ass;
}

/*
 * Parses an block statement - expects statements separated by separators, ended
 * by the 'end' keyword
 */
Statement* Parser::parseBlock(std::istream& is) {
    #ifdef DEBUG
        cout << "### Parsing block" << endl;
    #endif
    Token* t = tok->getToken(is, line);
    if(t->type == Token::KEYWORD && t->value == "end") {
        tok->tokenOK();
        delete t;
        return new Block(topLevel);
    }
    Block* b = new Block(topLevel);
    topLevel = false; // may contain other statements - they surely aren't top-level ones
    for(;;) {
        try {
            b->append(parseStmt(is));
            t = tok->getToken(is,line);
        }catch(NinjacException e) {
            delete b;
            throw e;
        }
        if(t->type == Token::KEYWORD && t->value == "end") break;
        if(t->type != Token::STMT_SEP) {
            throw NinjacException(false,"expected ';'",t->l);
        }
        tok->tokenOK();
        delete t;
    }
    tok->tokenOK();
    delete t;
    #ifdef DEBUG
        cout << "### block parsed" << endl;
    #endif
    return b;
}

/*
 * Parses a for-loop statement - expects:
 *  control variable 'from' expression 'to' expression ['step' expression] 'do' statement
 */
Statement* Parser::parseFor(std::istream& is) {
    #ifdef DEBUG
        cout << "### Parsing for-loop" << endl;
    #endif
    ForLoop* f = new ForLoop(parseVar(is),topLevel);
    topLevel = false; // contained statement surely isn't a top-level one
    try {
        expect("from",is);
        f->setFrom(parseExpr(is));
        expect("to",is);
        f->setTo(parseExpr(is));
        Token* t = tok->getToken(is, line);
        if(t->type != Token::KEYWORD || (t->value != "do" && t->value != "step")) {
            throw NinjacException(false,"expected \"do\" or \"step\"",t->l);
        }
        bool step = t->value == "step";
        tok->tokenOK();
        delete t;
        if(step) {
            f->setStep(parseExpr(is));
            expect("do",is);
        }else {
            f->setStep(new Constant(1.0));
        }
        f->setStatement(parseStmt(is));
    }catch(NinjacException e) {
        delete f;
        throw e;
    }
    #ifdef DEBUG
        cout << "### for-loop parsed" << endl;
    #endif
    return f;
}

/*
 * Parses a while-loop statement - expects: expression 'do' statement
 */
Statement* Parser::parseWhile(std::istream& is) {
    #ifdef DEBUG
        cout << "### Parsing while-loop" << endl;
    #endif
    WhileLoop* w = new WhileLoop(topLevel);
    topLevel = false; // contained statement surely isn't a top-level one
    try {
        w->setCond(parseExpr(is));
        expect("do",is);
        w->setStatement(parseStmt(is));
    }catch(NinjacException e) {
        delete w;
        throw e;
    }
    #ifdef DEBUG
        cout << "### while-loop parsed" << endl;
    #endif
    return w;
}

/*
 * Parses a repeat-loop statement - expects:
 *  [statements separated by separators] 'until' expression
 */
Statement* Parser::parseRepeat(std::istream& is) {
    #ifdef DEBUG
        cout << "### Parsing repeat-loop" << endl;
    #endif
    RepeatLoop* r = new RepeatLoop(topLevel);
    Block* b = new Block(false);
    r->setStatement(b);
    topLevel = false; // may contain other statements - they surely aren't top-level ones
    try {
        Token* t;
        for(;;) {
            b->append(parseStmt(is));
            t = tok->getToken(is,line); 
            if(t->type == Token::KEYWORD && t->value == "until") break;
            if(t->type != Token::STMT_SEP) {
                throw NinjacException(false,"expected ';'",t->l);
            }
            tok->tokenOK();
            delete t;
        }
        tok->tokenOK();
        delete t;
        r->setCond(parseExpr(is));
    }catch(NinjacException e) {
        delete r;
        throw e;
    }
    #ifdef DEBUG
        cout << "### repeat-loop parsed" << endl;
    #endif
    return r;
}

/*
 * Parses a function declaration statement - expects:
 *  function name ['of' variables separated by argument separators]
 *  'is' [statements separated by separators] 'return' expression
 */
Statement* Parser::parseFunc(std::istream& is) {
    #ifdef DEBUG
        cout << "### Parsing function declaration" << endl;
    #endif
    Token* t = tok->getToken(is,line);
    if(t->type != Token::FUNC) {
        throw NinjacException(false,"expected function name",t->l);
    }
    if(Globals::inst->getFuncs()->count(t->value) != 0) {   // check for existence
        ostringstream sout;
        sout << "function " << t->value << " is already declared";
        throw NinjacException(false,sout.str().c_str(),t->l);
    }
    FunctionDeclaration* fd = new FunctionDeclaration(t->value);
    Block* b = new Block(false);
    fd->setBody(b);
    tok->tokenOK();
    delete t;
    try {
        t = tok->getToken(is, line);
        if(t->type != Token::KEYWORD || (t->value != "of" && t->value != "is")) {
            throw NinjacException(false,"expected \"of\" or \"is\"",t->l);
        }
        bool args = t->value == "of";
        tok->tokenOK();
        delete t;
        if(args) {
            for(;;) {
                string arg = parseVar(is);
                if(fd->hasArgument(arg)) {
                    throw NinjacException(false,"argument name duplication",line);
                }
                fd->addArgument(arg);
                t = tok->getToken(is, line);
                if(t->type == Token::KEYWORD && t->value == "is") {
                    tok->tokenOK();
                    delete t;
                    break;
                }
                if(t->type != Token::ARG_SEP) {
                    throw NinjacException(false,"expected argument separator or \"is\"",t->l);
                }
                tok->tokenOK();
                delete t;
            }
        }
        // in either case, 'is' token was already acknowledged and deleted
        t = tok->getToken(is,line);
        if(t->type != Token::KEYWORD || t->value != "return") {
            for(;;) {
                b->append(parseStmt(is));
                t = tok->getToken(is,line);
                if(t->type == Token::KEYWORD && t->value == "return") break;
                if(t->type != Token::STMT_SEP) {
                    throw NinjacException(false,"expected ';'",t->l);
                }
                tok->tokenOK();
                delete t;
            }
        }
        tok->tokenOK();
        delete t;
        fd->setReturn(parseExpr(is));
    }catch(NinjacException e) {
        delete fd;
        throw e;
    }
    #ifdef DEBUG
        cout << "### function declaration parsed" << endl;
    #endif
    return fd;
}

/*
 * Parses a conditionaal branch statement - expects:
 *  expression 'then' statement ['else' statement]
 */
Statement* Parser::parseIf(std::istream& is) {
    #ifdef DEBUG
        cout << "### Parsing conditional branch" << endl;
    #endif
    Conditional* c = new Conditional(topLevel);
    topLevel = false; // contained statement surely isn't a top-level one
    try{
        c->setCondition(parseExpr(is));
        expect("then",is);
        c->setIfTrue(parseStmt(is));
        Token* t = tok->getToken(is, line);
        if(t->type == Token::KEYWORD && t->value == "else") {
            tok->tokenOK();
            delete t;
            c->setIfFalse(parseStmt(is));
        }
    }catch(NinjacException e) {
        delete c;
        throw e;
    }
    #ifdef DEBUG
        cout << "### conditional branch parsed" << endl;
    #endif
    return c;
}

/*
 * Checks for an expected keyword in the stream.
 *  Success = eats the token and returns nothing
 *  Failure = throws a NinjacException
 */
void Parser::expect(string keyword, istream& is) {
    Token* t = tok->getToken(is, line);
    if(t->type != Token::KEYWORD || t->value != keyword) {
        ostringstream sout;
        sout << "expected \"" << keyword << '\"';
        throw NinjacException(false,sout.str().c_str(),t->l);
    }
    tok->tokenOK();
    delete t;
}

/*
 * Checks for an expected variable token in the stream.
 *  Success = eats the token and returns variable name
 *  Failure = throws a NinjacException
 */
string Parser::parseVar(std::istream& is) {
    Token* t = tok->getToken(is, line);
    if(t->type != Token::VAR) {
        throw NinjacException(false,"expected a variable",t->l);
    }
    tok->tokenOK();
    string s = t->value;
    delete t;
    return s;
}

/*
 * The expression parser has two stages:
 *
 * 1. Dijkstra's Shunting-yard Algorithm (void shuntingYard(...))
 * 2. The tree constructor (this function)
 *      assembles the RPN token queue into an equivalent tree of Expression objects
 *      ready to be interpreted
 */
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

    stack<Expression*> stack;   // the main working stack - will contain the root Expression in the end
    std::stack<Expression*> tmpStack; // only a way to reorder function arguments correctly
    istringstream sin; // for string -> double conversion (constants)
    do {
        Token* t = out.front();
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
                                {Operator* op = getOperator(t->value,t->l);
                                if(stack.size() < 2) {
                                    delete op;
                                    clearExprs(stack,out);
                                    throw NinjacException(false,"not enough operands for operator",t->l);
                                }
                                op->setRight(stack.top());
                                stack.pop();
                                op->setLeft(stack.top());
                                stack.pop();
                                stack.push(op);
                                break;}
            case Token::FUNC:
                                FunctionCall* fc = new FunctionCall(t->value,t->l);
                                #ifdef DEBUG
                                    cout << "### Parsing function " << t->value << ", argc = " << t->argc << endl;
                                #endif
                                if(stack.size() < t->argc) {
                                    delete fc;
                                    clearExprs(stack,out);
                                    throw NinjacException(false,"missing argument(s)",t->l);
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
        delete t; // this is the final destination of even the most long-lived tokens
        out.pop();
    }while(!out.empty());

    #ifdef DEBUG
        assert(!stack.empty());
    #endif

    if(stack.size() > 1) {
        clearExprs(stack,out);
        throw NinjacException(false,"not an expression", line);
    }

    #ifdef DEBUG
        cout << "### Expression parsed" << endl;
    #endif

    return stack.top();
}

/*
 * purges containers when something goes wrong during tree-constructor execution
 */
void Parser::clearExprs(stack<Expression*>& stack, queue<Token*>& queue) {
    while(!stack.empty()) {
        delete stack.top();
        stack.pop();
    }
    while(!queue.empty()) {
        delete queue.front();
        queue.pop();
    }
}

/*
 *  This function implements Edsger Dijkstra's Shunting-yard Algorithm
 *  as described on http://en.wikipedia.org/wiki/Shunting_yard_algorithm
 *
 *  and converts the infix token stream into a simpler token queue representing
 *  the expression in reverse polish notation.
 */
void Parser::shuntingYard(istream& is, queue<Token*>& out) {
    std::stack<Token*> stack; // the main working stack
    std::stack<int> argCntStack; // function argument counter stack (correct argument count is unknown during parsing)
    bool end = false; // a flag

    try {
        do {
            Token* t = tok->getToken(is,line);
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
                                        throw NinjacException(false,"unmatched parthenses",t->l);
                                    }
                                    #ifdef DEBUG
                                        assert(stack.top()->type == Token::LEFT_P);
                                    #endif
                                    delete stack.top();
                                    stack.pop();
                                    if(!stack.empty() && stack.top()->type == Token::FUNC) {
                                        Token* f = stack.top();
                                        f->argc = argCntStack.top() + 1; // one for the parthensis itself - zero-argument functions don't have them
                                        argCntStack.pop();
                                        out.push(f);
                                        stack.pop();
                                    }
                                    delete t;
                                    tok->tokenOK();
                                    break;
                case Token::OPER:
                                    // simplification: NINJAC only has binary, left-associative operators -> the only thing to check is precedence
                                    while(!stack.empty() && ( stack.top()->type == Token::FUNC || (stack.top()->type == Token::OPER && tok->hasLTEpriority(t,stack.top())))){
                                        out.push(stack.top());
                                        stack.pop();
                                    }
                                    stack.push(t);
                                    tok->tokenOK();
                                    break;
                case Token::ARG_SEP:
                                    {while (!stack.empty() && stack.top()->type != Token::LEFT_P){
                                        out.push(stack.top());
                                        stack.pop();
                                    }
                                    if(stack.empty()) {
                                        throw NinjacException(false,"misplaced argument separator or unmatched parthenses",t->l);
                                    }
                                    int tmp = argCntStack.top()+1; // add a notch
                                    argCntStack.pop();
                                    argCntStack.push(tmp);
                                    delete t;
                                    tok->tokenOK();
                                    break;}
                default:
                                    end = true; // other token, not a part of the expression
                                    break;
            }
        }while(!end);
    }catch(NinjacException e) {
        clearTokens(stack,out);
        throw e;
    }

    while(!stack.empty()) {
        if(stack.top()->type == Token::LEFT_P) {
            int ln = stack.top()->l;
            clearTokens(stack,out);
            throw NinjacException(false,"unmatched parthenses",ln);
        }
        out.push(stack.top());
        stack.pop();
    }

    if(out.empty()) {
        clearTokens(stack,out);
        throw NinjacException(false,"expected an expression",line);
    }
}

/*
 * purges containers when something goes wrong during shunting-yard execution
 */
void Parser::clearTokens(stack<Token*>& stack, queue<Token*>& queue) {
    while(!stack.empty()) {
        delete stack.top();
        stack.pop();
    }
    while(!queue.empty()) {
        delete queue.front();
        queue.pop();
    }
}

/*
 * a convenient token-value-string to Operator-instance translator
 */
Operator* Parser::getOperator(string oper, int line) {
    if(oper == "+") return new PlusOperator();
    if(oper == "-") return new MinusOperator();
    if(oper == "/") return new DivOperator(line);
    if(oper == "*") return new MulOperator();
    if(oper == "\\") return new IntDivOperator(line);
    if(oper == "%") return new ModuloOperator(line);
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
