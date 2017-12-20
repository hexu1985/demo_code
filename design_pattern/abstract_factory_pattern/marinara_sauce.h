#ifndef __marinara_sauce_h
#define __marinara_sauce_h

#include <string>
#include "sauce.h"

class MarinaraSauce: public Sauce {
public:
    std::string toString() {
        return "MarinaraSauce";
    }
};

#endif


