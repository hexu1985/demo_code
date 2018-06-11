#include <iostream>
#include "base.h"

using namespace std;

Base::~Base() {}

int Base::f() { return 0; };

void b(Base *base) { cout << base->f() << endl; };
