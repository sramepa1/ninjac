#ifndef _GLOBALS_H
#define	_GLOBALS_H

#include <map>
#include <string>
#include <stack>

#include "parser.h"
#include "block.h"
#include "functions.h"

class Globals {

public:
            bool            ia          () const            { return interactive; }
            Block*          getProg     () const            { return program; }
            Parser*         getPars     () const            { return parser; }

            std::map<std::string,double>*
                            getVars     () const            { return globalVars; }
            std::stack<std::map<std::string,double>*>*
                            getLocalVars() const            { return localVarStack; }
            std::map<std::string,func*>*
                            getFuncs    () const            { return functions; }

            void            assignVar   (std::string var, double val);
            void            resetProg   ();

    friend  int             main        (int argc, char*argv[]);

            double          delta;

    static  Globals* const  inst;

private:
                            Globals     ();
                           ~Globals     ();

            void            initBuiltIn ();

                            Globals     (const Globals& src)    { }                 //DISABLED
            Globals         operator=   (const Globals& src)    { return *this; }   //DISABLED

            bool            interactive;

            Block*          program;
            Parser*         parser;

            std::map<std::string,double>*
                            globalVars;
            std::stack<std::map<std::string,double>*>*
                            localVarStack;
            std::map<std::string,func*>*
                            functions;
};

#endif	/* _GLOBALS_H */