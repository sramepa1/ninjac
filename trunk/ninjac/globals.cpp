#include "globals.h"
#include "parser.h"
#include "block.h"

Globals::Globals() {
    interactive = true;
    parser = new Parser();
    program = new Block();
}

Globals::~Globals() {
    delete parser;
    delete program;
}

void Globals::resetProg() {
    delete program;
    program = new Block();
}


Globals* const Globals::inst = new Globals();
