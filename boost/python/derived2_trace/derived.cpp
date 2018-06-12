#include <iostream>
#include "derived.h"

using namespace std;

Derived::Derived() 
{
    cout << "Derived::Derived() called, "
        << "this = " << this << endl;
}

Derived::~Derived() 
{
    cout << "Derived::~Derived() called, "
        << "this = " << this << endl;
}

string Derived::getName() { return "Derived"; }
