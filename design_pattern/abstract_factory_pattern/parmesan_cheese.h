#ifndef __parmesan_cheese_h
#define __parmesan_cheese_h

#include <string>
#include "cheese.h"

class ParmesanCheese: public Cheese {
public:
    std::string toString() {
        return "Shredded Parmesan";
    }
};

#endif


