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

#include "block.h"
#include "globals.h"

using namespace std;

// this code does not really need any comments

Block::~Block() {
    for (unsigned int i = 0; i < statements.size(); i++) {
        delete statements[i];
    }
}

void Block::execute() {
    #ifdef DEBUG
        cout << "### commencing block execution" << endl;
    #endif

    int size = statements.size();
    for (int i = 0; i < size; i++) {

        #ifdef DEBUG
            cout << "### executing statement " << i+1 << " of " << size << " in block" << endl;
        #endif

        statements[i]->execute();
    }

    if(Globals::inst->ia() && topLevel) {
        cout << "#> OK" << endl;
    }
    
    #ifdef DEBUG
        cout << "### block execution done" << endl;
    #endif
}

void Block::append(Statement* s) {
    statements.push_back(s);
}
