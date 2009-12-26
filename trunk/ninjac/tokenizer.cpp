#include <string>
#include <cstring>

#include "parser.h"
#include "ninjacexcept.h"

using namespace std;

Tokenizer::Tokenizer(Parser* p) {
    parser = p;
    cache = NULL;
    lastToken = Token::END;

    prior["*"] = 6;
    prior["/"] = 6;
    prior["\\"] = 6;
    prior["%"] = 6;

    prior["+"] = 5;
    prior["-"] = 5;

    prior["<"] = 4;
    prior[">"] = 4;
    prior["<="] = 4;
    prior[">="] = 4;

    prior["="] = 3;
    prior["=="] = 3;
    prior["<>"] = 3;

    prior["&"] = 2;
    prior["&&"] = 2;

    prior["|"] = 1;
    prior["||"] = 1;
}

Tokenizer::~Tokenizer() {
    if(cache != NULL) delete cache;
}

Token* Tokenizer::getToken(istream& is, int& line) {
    if(cache != NULL) return cache;
    char c;
    Token* t = new Token;
    bool comment = false;

    #ifdef DEBUG
        cout << "### Reading token from stream. is.good() == " << boolalpha << is.good() << noboolalpha << endl;
    #endif

    do {
        is >> c; // formatted input for the purpose of linebreak conversion
        if(!is.good()) {
            #ifdef DEBUG
                cout << "### Tokenizer reached end of stream" << endl;
            #endif
            t->type = Token::END;
            t->l = line;
            return t;
        }
        if(c == '\n') {
            line++;
            comment = false;
        }else if(c == '#') {
            comment = true;
        }
    }while(isspace(c) || comment);


    if(c=='(') {
        t->type = Token::LEFT_P;
    }else if(c==')') {
        t->type = Token::RIGHT_P;
    }else if(c==',') {
        t->type = Token::ARG_SEP;
    }else if(c==';') {
        t->type = Token::STMT_SEP;
    }else if(c==':') {
        t->type = Token::ASSIGN;
        if(is.peek() == '=') {
            is.get();
        }
    }else if(isdigit(c) || (c=='-' && lastToken!=Token::NUM && lastToken!=Token::FUNC && lastToken!=Token::RIGHT_P && lastToken!=Token::VAR)) {
        t->type = Token::NUM;
        t->value.append(1,c);
        if( c=='-' && !isdigit(is.peek())) {
            t->type = Token::OPER;
        }else {
            for(;;){
                c = is.peek();
                if(isdigit(c) || c == '.') {
                    is >> c;
                    t->value.append(1,c);
                }else break;
            }
        }
    }else if(c=='$') {
        t->type = Token::VAR;
        if(!isalpha(is.peek())) {
            delete t;
            throw NinjacException(false,"expected variable name",line);
        }
        for(;;){
            c = is.peek();
            if(isalpha(c)) {
                is >> c;
                t->value.append(1,c);
            }else break;
        }
    }else if(isalpha(c)) {
        t->value.append(1,c);
        for(;;){
            c = is.peek();
            if(isalpha(c)) {
                is >> c;
                t->value.append(1,c);
            }else break;
        }
        t->type = parser->keywords.count(t->value) == 0 ? Token::FUNC : Token::KEYWORD;
    }else if(parser->oneCharOper.find(c) != string::npos) {
        t->type = Token::OPER;
        t->value.append(1,c);
        string tmp;
        tmp.append(1,c);
        tmp.append(1,(char)is.peek());
        if(parser->twoCharOper.count(tmp) != 0) {
            t->value.append(1,(char)is.get());
        }
    }else {
        delete t;
        char buf[24] = "unexpected character: X";
        buf[22] = c;
        throw NinjacException(false,buf,line);
    }

    if(is.fail()) {
        delete t;
        throw NinjacException(false,"unexpected end of stream",line);
    }

    lastToken = t->type;
    cache = t;

    t->l = line;
    t->argc = 0;

    return t;
}

void Tokenizer::tokenOK() {
    cache = NULL;
}

void Tokenizer::reset() {
    if(cache != NULL) delete cache;
    lastToken = Token::END;
}

bool Tokenizer::hasLTEpriority(Token* first, Token* second) {
    #ifdef DEBUG
        assert(first->type == Token::OPER && second->type == Token::OPER);
    #endif
    return prior[first->value] <= prior[second->value];
}
