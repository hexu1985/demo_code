#ifndef __base_h
#define __base_h

struct Base
{
    virtual ~Base();
    virtual int f();
};

void b(Base *base);

#endif
