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
#ifndef _GLOBALS_H
#define	_GLOBALS_H

#include <map>
#include <string>
#include <stack>

#include "parser.h"
#include "block.h"
#include "functions.h"

/*
 * The Globals class is the centerpoint singleton of NINJAC.
 * Stores support structures for the interpreter core (variable maps, function map)
 * as well as the parser an the parsed program tree itself
 *
 * NINJAC is designed with the "optimistic programming" mantra in mind,
 * rather than "defensive programming", which means that encapsulation is
 * quite weak, especially because Globals mostly stores pointers,
 * but as it's my code using them, I don't see a problem in this.
 *
 * Method / attribute names should be self-documenting, some more info is in .cpp
 */
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

    friend  int             main        (int argc, char*argv[]); // to initialize the interactive bool

            double          delta; // the default threshold for zero and equality checking

    static  Globals* const  inst; // pointer to the instance of this singleton

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
