#ifndef _NINJACEXCEPT_H
#define	_NINJACEXCEPT_H

class NinjacException {
    
public:
                    NinjacException (bool runtime, const char* msg, int line, int column);

    const   char *  getMsg          () const    { return &(message[0]); }
            int     getLine         () const    { return l; }
            int     getColumn       () const    { return c; }
            bool    isRuntime       () const    { return runt; }

protected:
            char    message[64];
            int     l;
            int     c;
            bool    runt;
};

class ExitException {};

#endif	/* _NINJACEXCEPT_H */
