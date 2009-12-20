#ifndef _GLOBALS_H
#define	_GLOBALS_H

#include "parser.h"
#include "block.h"

class Globals {

public:
            bool            ia          () const            { return interactive; }
            Block*          getProg     () const            { return program; }
            Parser*         getPars     () const            { return parser; }

            void            resetProg   ();

    friend  int             main        (int argc, char*argv[]);

    static  double          delta;

    static  Globals* const  inst;

private:
                            Globals     ();
                           ~Globals     ();

                            Globals     (const Globals& src)    { }                 //DISABLED
            Globals         operator=   (const Globals& src)    { return *this; }   //DISABLED

            bool            interactive;
            Block*          program;
            Parser*         parser;
};

#endif	/* _GLOBALS_H */
