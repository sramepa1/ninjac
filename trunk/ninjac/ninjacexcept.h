#ifndef _NINJACEXCEPT_H
#define	_NINJACEXCEPT_H

class NinjacException {
    
public:
                    NinjacException (bool runtime, const char* msg, int line);

    const   char *  getMsg          () const    { return &(message[0]); }
            int     getLine         () const    { return l; }
            bool    isRuntime       () const    { return runt; }

protected:
            char    message[64];
            int     l;
            bool    runt;
};

class ExitException {};

#endif	/* _NINJACEXCEPT_H */
