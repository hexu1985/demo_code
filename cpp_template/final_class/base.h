#ifndef __base_h
#define __base_h

#include "final_class.h"

class Base: virtual Final_class<Base> {
public:
    Base() {}
};

#endif
