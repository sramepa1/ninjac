#include "block.h"

#ifdef DEBUG
    #include <iostream>
#endif

using namespace std;

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
    
    #ifdef DEBUG
        cout << "### block execution done" << endl;
    #endif
}

void Block::append(Statement* s) {
    statements.push_back(s);
}
