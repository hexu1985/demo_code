#ifndef __gumball_machine_h
#define __gumball_machine_h

#include "state.h"
#include "sold_out_state.h"
#include "no_quarter_state.h"
#include "has_quarter_state.h"
#include "sold_state.h"
#include "winner_state.h"
#include <memory>
#include <string>
#include <iostream>

class GumballMachine {
private: 
    std::shared_ptr<State> soldOutState;
	std::shared_ptr<State> noQuarterState;
	std::shared_ptr<State> hasQuarterState;
	std::shared_ptr<State> soldState;
	std::shared_ptr<State> winnerState;
 
	std::shared_ptr<State> state;
	int count = 0;
 
public:
	GumballMachine(int numberGumballs) {
		soldOutState = std::make_shared<SoldOutState>(*this);
		noQuarterState = std::make_shared<NoQuarterState>(*this);
		hasQuarterState = std::make_shared<HasQuarterState>(*this);
		soldState = std::make_shared<SoldState>(*this);
		winnerState = std::make_shared<WinnerState>(*this);

        state = soldOutState;
		this->count = numberGumballs;
 		if (numberGumballs > 0) {
			state = noQuarterState;
		} 
	}
 
	void insertQuarter() {
		state->insertQuarter();
	}
 
	void ejectQuarter() {
		state->ejectQuarter();
	}
 
	void turnCrank() {
		state->turnCrank();
		state->dispense();
	}

	void setState(std::shared_ptr<State> state) {
		this->state = state;
	}
 
	void releaseBall() {
        std::cout << "A gumball comes rolling out the slot..." << "\n";
		if (count != 0) {
			count = count - 1;
		}
	}
 
	int getCount() {
		return count;
	}
 
	void refill(int count) {
		this->count = count;
		state = noQuarterState;
	}

    std::shared_ptr<State> getState() {
        return state;
    }

    std::shared_ptr<State> getSoldOutState() {
        return soldOutState;
    }

    std::shared_ptr<State> getNoQuarterState() {
        return noQuarterState;
    }

    std::shared_ptr<State> getHasQuarterState() {
        return hasQuarterState;
    }

    std::shared_ptr<State> getSoldState() {
        return soldState;
    }
 
    std::shared_ptr<State> getWinnerState() {
        return winnerState;
    }
 
    std::string toString() const {
        std::string result;
        result += "\nMighty Gumball, Inc.";
        result += "\nJava-enabled Standing Gumball Model #2004\n";
        result += "Inventory: " + std::to_string(count) + " gumball";
        if (count != 1) {
            result += "s";
        }
        result += "\nMachine is " + state->toString() + "\n";
        return std::move(result);
	}
};

inline
std::ostream &operator <<(std::ostream &out, const GumballMachine &gumball_machine)
{
    out << gumball_machine.toString();
    return out;
}

#endif
