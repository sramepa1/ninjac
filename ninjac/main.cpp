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
#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <sstream>

#include "globals.h"
#include "parser.h"
#include "ninjacexcept.h"

using namespace std;

int handleInteractive();
int handleScript();
void printEx(const NinjacException& e);

/*
 * Provides the -s switch for interactive mode, calls appropriate handler
 * and does return value handling & final cleanup.
 */
int main(int argc, char* argv[]) {
    if(argc > 2 || (argc == 2 && strcmp(argv[1],"-s") != 0)) {
        cout << "Usage: \"" << argv[0] << "\" for interactive mode or \"" << argv[0] << " -s\" for script mode." << endl;
        return 1;
    }

    Globals::inst->interactive = argc == 1;

    cout << setprecision(12); // default value

    int exitStatus = 1;
    try{
        if(Globals::inst->ia()) {
            cout << "Welcome to NINJAC 1.0 interactive mode. NINJAC Is Not Just A Calculator!" << endl
                 << "Enter statements or expressions, \"exit\" statement terminates." << endl;
            exitStatus = handleInteractive();
        }else {
            exitStatus = handleScript();
        }
    }catch(ExitException e) {
        cout << "#> Terminating on user request." << endl;
        exitStatus = 0;
    }
    delete Globals::inst;
    return exitStatus;
}

/*
 * Repeats parsing and execution on individual input lines, prints exception messages.
 */
int handleInteractive() {
    string line;
    istringstream sin;
    for(;;) { // Loop will be broken by the exception thrown when "exit" statement is executed
        getline(cin,line);
        if(cin.fail() || cin.bad()) return 1;
        sin.str(line);
        try{            
            Globals::inst->getPars()->parse(sin);
            Globals::inst->getProg()->execute();
        }catch(NinjacException e) {
            printEx(e);
        }
        Globals::inst->resetProg();
        sin.clear();
    }    
}

/*
 * Parses and executes the entire content of the standard input stream, halts on exceptions.
 */
int handleScript() {
    try {
        Globals::inst->getPars()->parse(cin);
        Globals::inst->getProg()->execute();
        return 0;
    }catch(NinjacException e) {
        printEx(e);
        cout << "#>   on line " << e.getLine() << ". Terminating." << endl;
        return 1;
    }
}

/*
 * Does not really need a comment.
 */
void printEx(const NinjacException& e) {
    cout << "#> " << (e.isRuntime() ? "Runtime" : "Parse" ) <<" error: " << e.getMsg() << endl;
}
