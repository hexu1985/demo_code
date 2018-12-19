#ifndef __has_quarter_state_h
#define __has_quarter_state_h

#include "state.h"
#include <random>

class GumballMachine; 

class HasQuarterState: public State {
private: 
    std::default_random_engine dre;
    std::uniform_int_distribution<int> di;
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
