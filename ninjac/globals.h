/* 
 * File:   globals.h
 * Author: Pavel
 *
 * Created on 9. prosinec 2009, 15:58
 */

#ifndef _GLOBALS_H
#define	_GLOBALS_H

#include "parser.h"
#include "block.h"

class Globals {

public:

    friend  int         main        (int argc, char*argv[]);

            bool        ia          () const                    {return interactive;}
            Block*      getProg     () const                    {return program;}
            Parser*     getPars     () const                    {return parser;}

            void        resetProg   ();

    static Globals* const inst;

private:
                Globals();
               ~Globals();

    bool        interactive;
    Block*      program;
    Parser*     parser;
};

#endif	/* _GLOBALS_H */

