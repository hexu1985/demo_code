#ifndef __state_h
#define __state_h

#include <string>

class State {
public: 
    virtual ~State();
    virtual void insertQuarter() = 0;
    virtual void ejectQuarter() = 0;
    virtual void turnCrank() = 0;
    virtual void dispense() = 0;
    virtual std::string toString() const = 0;
};

#endif
