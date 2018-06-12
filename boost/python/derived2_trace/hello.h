#ifndef __hello_h
#define __hello_h

#include <memory>

struct Base;
struct Derived;

void b(Base *base);

void d(Derived *derived);

Base *factory();

std::shared_ptr<Base> factory2();

void b2(std::shared_ptr<Base> base);

#endif
