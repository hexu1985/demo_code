#ifndef __plum_tomato_sauce_h
#define __plum_tomato_sauce_h

#include <string>
#include "sauce.h"

class PlumTomatoSauce: public Sauce {
public:
    std::string toString() {
        return "Tomato sauce with plum tomatoes";
    }
};

#endif


