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


int main(int argc, char* argv[]) {
    if(argc > 2 || (argc == 2 && strcmp(argv[1],"-s") != 0)) {
        cout << "Usage: \"" << argv[0] << "\" for interactive mode or \"" << argv[0] << " -s\" for script mode." << endl;
        return 1;
    }

    Globals::inst->interactive = argc == 1;

    cout << setprecision(12);

    int exitStatus = 1;
    try{
        if(Globals::inst->ia()) {
            cout << "Welcome to NINJAC 0.5 beta interactive mode. NINJAC Is Not Just A Calculator!" << endl;
            cout << "Enter statements or expressions, \"exit\" statement terminates." << endl;
            exitStatus = handleInteractive();
        }else {
            exitStatus = handleScript();
        }
    }catch(ExitException e) {
        cout << "#> Terminating on user request." << endl;
        exitStatus = 0;
    }catch(NinjacException e) {
        printEx(e);
        cout << "#>   on line " << e.getLine() << ". Terminating." << endl;
    }
    delete Globals::inst;
    return exitStatus;
}

int handleInteractive() {
    string tmp;
    istringstream sin;
    for(;;) { // Will be terminated by user-abort exception thrown when "exit" statement is executed
        getline(cin,tmp);
        if(cin.fail()) return -1;
        try{
            sin.str(tmp);
            Globals::inst->getPars()->parse(sin);
            Globals::inst->getProg()->execute();
        }catch(NinjacException e) {
            printEx(e);
        }
        Globals::inst->resetProg();
        sin.clear();
    }    
}

int handleScript() {
    Globals::inst->getPars()->parse(cin);
    Globals::inst->getProg()->execute();
    return 0;
}

void printEx(const NinjacException& e) {
    cout << "#> " << (e.isRuntime() ? "Runtime" : "Parse" ) <<" error: " << e.getMsg() << endl;
}
