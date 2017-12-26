#ifndef __mozzarella_cheese_h
#define __mozzarella_cheese_h

#include <string>
#include "cheese.h"

class MozzarellaCheese: public Cheese {
public:
    std::string toString() {
        return "Shredded Mozzarella";
    }
};

#endif


