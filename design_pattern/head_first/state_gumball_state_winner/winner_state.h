#ifndef __winner_state_h
#define __winner_state_h

#include "state.h"

class GumballMachine; 

class WinnerState: public State {
private: 
    GumballMachine &gumballMachine;

public:
    WinnerState(GumballMachine &gumballMachine);
       
	void insertQuarter() override;
	void ejectQuarter() override;
	void turnCrank() override;
	void dispense() override;
    std::string toString() const override;
};

#endif
