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
#ifndef _NINJACEXCEPT_H
#define	_NINJACEXCEPT_H

/*
 * Internal exception class - only a little more than a struct.
 */
class NinjacException {
    
public:
                    NinjacException (bool runtime, const char* msg, int line);

    const   char *  getMsg          () const    { return &(message[0]); }
            int     getLine         () const    { return l; }
            bool    isRuntime       () const    { return runt; }

protected:
            char    message[64];    // fixed-size is enough
            int     l;              // line of code of exception's cause in script source
            bool    runt;           // true = runtime exception, false = parse exception
};

/*
 *  Thrown by ExitStatement execution, used to terminate program on user request.
 *  Caught in main(), does not need any extra fields - its type carries the meaning.
 */
class ExitException {};

#endif	/* _NINJACEXCEPT_H */
