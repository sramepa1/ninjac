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

#include <string>
#include <cstring>

#include "parser.h"
#include "ninjacexcept.h"

using namespace std;

/*
 * Yet another boring initialization
 */
Tokenizer::Tokenizer(Parser* p) {
    parser = p;
    cache = NULL;
    lastToken = Token::END;

    // priorities taken from C
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

/*
 * Deletes the last leftover token if necessary. More info on cache coming soon.
 */
Tokenizer::~Tokenizer() {
    if(cache != NULL) delete cache;
}

/*
 * Returns the next token in the stream.
 *
 * Mechanism works this way:
 *  - if cache is NULL, the token is created, actually read from the character stream,
 *    stored in the cache and then returned
 *  - if there already is a token in the cache, it is returned and nothing is done
 *    to the stream.
 *
 *  - if the returned token was what the calling parser function was expecting,
 *    ownership is transferred (parser stores and/or deletes the token)
 *    and parser acknowledges this by calling tokenOK, which sets cache to NULL.
 *
 *  - if this was not expected (for example a keyword that followed expression tokens),
 *    the parser just leaves the token in cache and finishes its job.
 *    The next parsing function to call getToken will then receive another pointer
 *    to the same Token.
 *
 * This ensures that parsing functions can "taste" what's in the stream without a penalty,
 * as long as a taste of one Token is enough (in NINJAC's language, it is)
 */
Token* Tokenizer::getToken(istream& is, int& line) {
    if(cache != NULL) return cache;
    char c;
    Token* t = new Token;
    bool comment = false;

    // skip whitespace and comments
    do {
        is >> c; // formatted input for the purpose of linebreak conversion
        if(!is.good()) {
            #ifdef DEBUG
                cout << "### Tokenizer reached end of stream" << endl;
            #endif
            t->type = Token::END;
            t->l = line;
            cache = t;
            return t;
        }
        if(c == '\n') {
            line++;
            comment = false;
        }else if(c == '#') {
            comment = true;
        }
    }while(isspace(c) || comment);

    // identify token
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
        /* That if-monstrosity is because "-" followed by a digit is the only ambiguous thing in the NINJAC language.
         * It may be the beginning of a constant *OR* an operator followed by a constant.
         * And since this is a single-pass parser, I can't guess and then go back in the stream
         * (it won't be even possible with cin).
         * So I keep track of what was the last token to determine whether it could
         * be folloewd by a negative constant or not.
         */
        t->type = Token::NUM;
        t->value.append(1,c);
        if( c=='-' && !isdigit(is.peek())) {
            t->type = Token::OPER; //negative constant could have been here, but it actually was an operator
        }else {
            for(;;){
                c = is.peek();
                if(isdigit(c) || c == '.') {
                    is >> c;
                    t->value.append(1,c); // store the string char-by-char
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
        t->type = parser->keywords.count(t->value) == 0 ? (int)Token::FUNC : (int)Token::KEYWORD;
    }else if(parser->oneCharOper.find(c) != string::npos) {
        t->type = Token::OPER;
        t->value.append(1,c);
        string tmp;
        tmp.append(1,c);
        tmp.append(1,(char)is.peek()); // try to construct two chars
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

/*
 * As described above, the parser acknowledges Token reception and ownership transfer
 * by calling this.
 */
void Tokenizer::tokenOK() {
    cache = NULL;
}

/*
 * resets tokenizer state
 */
void Tokenizer::reset() {
    if(cache != NULL) {
        delete cache;
        cache = NULL;
    }
    lastToken = Token::END;
}

/*
 * Called by the Shunting-yard function to determine operator precedence,
 * this uses a lookup table to determine whether the first operator token
 * has lower than or equal precedence than the second operator token
 */
bool Tokenizer::hasLTEpriority(Token* first, Token* second) {
    #ifdef DEBUG
        assert(first->type == Token::OPER && second->type == Token::OPER);
    #endif
    return prior[first->value] <= prior[second->value];
}
