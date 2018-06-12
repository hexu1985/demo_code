#include <iostream>
#include "base.h"

using namespace std;

Base::Base() 
{
    cout << "Base::Base() called, "
        << "this = " << this << endl;
}

Base::~Base() 
{
    cout << "Base::~Base() called, "
        << "this = " << this << endl;
}

string Base::getName() { return "Base"; }

