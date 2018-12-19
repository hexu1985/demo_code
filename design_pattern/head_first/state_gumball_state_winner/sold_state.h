#ifndef __sold_state_h
#define __sold_state_h

#include "state.h"

class GumballMachine; 

class SoldState: public State {
private: 
    GumballMachine &gumballMachine;

public:
    SoldState(GumballMachine &gumballMachine);
       
	void insertQuarter() override;
	void ejectQuarter() override;
	void turnCrank() override;
	void dispense() override;
    std::string toString() const override;
};

#endif
