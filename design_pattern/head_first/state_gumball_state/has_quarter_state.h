#ifndef __has_quarter_state_h
#define __has_quarter_state_h

#include "state.h"

class GumballMachine; 

class HasQuarterState: public State {
private: 
    GumballMachine &gumballMachine;

public:
    HasQuarterState(GumballMachine &gumballMachine);
       
	void insertQuarter() override;
	void ejectQuarter() override;
	void turnCrank() override;
	void dispense() override;
    std::string toString() const override;
};

#endif
