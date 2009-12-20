#ifndef _NINJACEXCEPT_H
#define	_NINJACEXCEPT_H

#include <cstring>

class NinjacException {
    
public:
                    NinjacException (bool runtime, const char* msg, int line, int column)

                                        { runt = runtime; l = line; c = column;
                                          strncpy(message,msg,sizeof(message));
                                          message[sizeof(message)-1]='\0'; }

    const   char *  getMsg          ()  { return &(message[0]); }
            int     getLine         ()  { return l; }
            int     getColumn       ()  { return c; }

protected:
            char    message[64];
            int     l;
            int     c;
            bool    runt;
};

#endif	/* _NINJACEXCEPT_H */
