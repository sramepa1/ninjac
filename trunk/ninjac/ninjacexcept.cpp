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
#include <cstring>

#include "ninjacexcept.h"

NinjacException::NinjacException (bool runtime, const char* msg, int line) {
    runt = runtime;
    l = line;
    strncpy(message, msg, sizeof(message)); // msg will usually be shorter than message, so strncpy will usually add the terminator,..
    message[sizeof(message) - 1] = '\0'; // ...but I will artificially terminate anyway
}
