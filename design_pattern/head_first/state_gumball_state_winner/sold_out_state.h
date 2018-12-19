#ifndef __sold_out_state_h
#define __sold_out_state_h

#include "state.h"

class GumballMachine; 

class SoldOutState: public State {
private: 
    GumballMachine &gumballMachine;

public:
    SoldOutState(GumballMachine &gumballMachine);
       
	void insertQuarter() override;
	void ejectQuarter() override;
	void turnCrank() override;
	void dispense() override;
    std::string toString() const override;
};

#endif
