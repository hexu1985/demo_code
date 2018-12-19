#ifndef __no_quarter_state_h
#define __no_quarter_state_h

#include "state.h"

class GumballMachine; 

class NoQuarterState: public State {
private: 
    GumballMachine &gumballMachine;

public:
    NoQuarterState(GumballMachine &gumballMachine);
       
	void insertQuarter() override;
	void ejectQuarter() override;
	void turnCrank() override;
	void dispense() override;
    std::string toString() const override;
};

#endif
