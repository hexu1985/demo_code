#ifndef __menu_h
#define __menu_h

#include <memory>
#include "iterator.h"

class Menu {
public:
    virtual std::shared_ptr<Iterator> createIterator() = 0;
};

#endif
