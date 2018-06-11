#ifndef __hello_h
#define __hello_h

struct Base;
struct Derived;

void b(Base *base);

void d(Derived *derived);

Base *factory();

#endif
