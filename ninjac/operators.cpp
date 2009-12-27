#include <cmath>

#ifdef DEBUG
    #include <iostream>
    #include <cassert>
    using namespace std;
#endif

#include "operators.h"
#include "globals.h"
#include "ninjacexcept.h"

Operator::~Operator() {
    if(left != NULL) delete left;
    if(right != NULL) delete right;
}

void Operator::setLeft(Expression* l) {
    #ifdef DEBUG
        assert(!left);
        assert(l);
    #endif

    left = l;
}

void Operator::setRight(Expression* r) {
    #ifdef DEBUG
        assert(!right);
        assert(r);
    #endif

    right = r;
}


double PlusOperator::evaluate() const {
    #ifdef DEBUG
        cout << "### evaluating addition" << endl;
        assert(left);
        assert(right);
    #endif

    double l = left->evaluate();
    double r = right->evaluate();

    #ifdef DEBUG
        cout << "### adding " << l << " + " << r << endl;
    #endif

    return l + r;
}

double MinusOperator::evaluate() const {
    #ifdef DEBUG
        cout << "### evaluating substraction" << endl;
        assert(left);
        assert(right);
    #endif

    double l = left->evaluate();
    double r = right->evaluate();

    #ifdef DEBUG
        cout << "### substracting " << l << " - " << r << endl;
    #endif

    return l - r;
}

double MulOperator::evaluate() const {
    #ifdef DEBUG
        cout << "### evaluating multiplication" << endl;
        assert(left);
        assert(right);
    #endif

    double l = left->evaluate();
    double r = right->evaluate();

    #ifdef DEBUG
        cout << "### multiplying " << l << " * " << r << endl;
    #endif

    return l * r;
}

double DivOperator::evaluate() const {
    #ifdef DEBUG
        cout << "### evaluating division" << endl;
        assert(left);
        assert(right);
    #endif

    double numer = left->evaluate();
    double denom = right->evaluate();
    if(fabs(denom) <= Globals::inst->delta) {
        throw NinjacException(true,"division by zero",l);
    }    

    #ifdef DEBUG
        cout << "### dividing " << numer << " / " << denom << endl;
    #endif

    return numer/denom;
}

double IntDivOperator::evaluate() const {
    #ifdef DEBUG
        cout << "### evaluating integer division" << endl;
        assert(left);
        assert(right);
    #endif

    double numer = round(left->evaluate());
    double denom = round(right->evaluate());
    if( fabs(numer) > (double)LONG_MAX || fabs(denom) > (double)LONG_MAX ) {
        throw NinjacException(true,"operand too large for integer division",l);
    }
    if(denom == 0) {
        throw NinjacException(true,"division by zero",l);
    }

    #ifdef DEBUG
        cout << "### dividing " << numer << " \\ " << denom << endl;
    #endif

    return (double)((long)numer/(long)denom);
}

double ModuloOperator::evaluate() const {
    #ifdef DEBUG
        cout << "### evaluating modulo" << endl;
        assert(left);
        assert(right);
    #endif

    double numer = round(left->evaluate());
    double denom = round(right->evaluate());
    if( fabs(numer) > (double)LONG_MAX || fabs(denom) > (double)LONG_MAX ) {
        throw NinjacException(true,"operand too large for modulo calculation",l);
    }
    if(denom == 0) {
        throw NinjacException(true,"division by zero",l);
    }

    #ifdef DEBUG
        cout << "### calculating " << numer << " % " << denom << endl;
    #endif

    return (double)((long)numer % (long)denom);
}

double AndOperator::evaluate() const {
    #ifdef DEBUG
        cout << "### evaluating AND" << endl;
        assert(left);
        assert(right);
    #endif

    double l = left->evaluate();
    if(fabs(l) <= Globals::inst->delta) {
        #ifdef DEBUG
            cout << "### short-circuit AND: left operand is false -> returning false" << endl;
        #endif
        return 0.0;
    }

    #ifdef DEBUG
        cout << "### short-circuit AND: left operand is true -> returning right operand" << endl;
    #endif
    return fabs(right->evaluate()) <= Globals::inst->delta ? 0.0 : 1.0;
}

double OrOperator::evaluate() const {
    #ifdef DEBUG
        cout << "### evaluating OR" << endl;
        assert(left);
        assert(right);
    #endif

    double l = left->evaluate();
    if(fabs(l) > Globals::inst->delta) {
        #ifdef DEBUG
            cout << "### short-circuit OR: left operand is true -> returning true" << endl;
        #endif
        return 1.0;
    }
    
    #ifdef DEBUG
        cout << "### short-circuit OR: left operand is false -> returning right operand" << endl;
    #endif
    return fabs(right->evaluate()) <= Globals::inst->delta ? 0.0 : 1.0;
}

double EqualsOperator::evaluate() const {
    #ifdef DEBUG
        cout << "### evaluating equality" << endl;
        assert(left);
        assert(right);
    #endif

    double l = left->evaluate();
    double r = right->evaluate();

    #ifdef DEBUG
        cout << "### testing whether " << l << " == " << r << endl;
    #endif

    return fabs(l-r) <= Globals::inst->delta ? 1.0 : 0.0;
}

double NotEqualsOperator::evaluate() const {
    #ifdef DEBUG
        cout << "### evaluating unequality" << endl;
        assert(left);
        assert(right);
    #endif

    double l = left->evaluate();
    double r = right->evaluate();

    #ifdef DEBUG
        cout << "### testing whether " << l << " != " << r << endl;
    #endif

    return fabs(l-r) > Globals::inst->delta ? 1.0 : 0.0;
}

double LessOperator::evaluate() const {
    #ifdef DEBUG
        cout << "### evaluating less than" << endl;
        assert(left);
        assert(right);
    #endif

    double l = left->evaluate();
    double r = right->evaluate();

    #ifdef DEBUG
        cout << "### testing whether " << l << " < " << r << endl;
    #endif

    return l < (r - Globals::inst->delta) ? 1.0 : 0.0;
}

double LTEOperator::evaluate() const {
    #ifdef DEBUG
        cout << "### evaluating less than or equal" << endl;
        assert(left);
        assert(right);
    #endif

    double l = left->evaluate();
    double r = right->evaluate();

    #ifdef DEBUG
        cout << "### testing whether " << l << " <= " << r << endl;
    #endif

    return l <= (r + Globals::inst->delta) ? 1.0 : 0.0;
}

double GreaterOperator::evaluate() const {
    #ifdef DEBUG
        cout << "### evaluating greater than" << endl;
        assert(left);
        assert(right);
    #endif

    double l = left->evaluate();
    double r = right->evaluate();

    #ifdef DEBUG
        cout << "### testing whether " << l << " > " << r << endl;
    #endif

    return l > (r + Globals::inst->delta) ? 1.0 : 0.0;
}

double GTEOperator::evaluate() const {
    #ifdef DEBUG
        cout << "### evaluating greater than or equal" << endl;
        assert(left);
        assert(right);
    #endif

    double l = left->evaluate();
    double r = right->evaluate();

    #ifdef DEBUG
        cout << "### testing whether " << l << " >= " << r << endl;
    #endif

    return l >= (r - Globals::inst->delta) ? 1.0 : 0.0;
}
