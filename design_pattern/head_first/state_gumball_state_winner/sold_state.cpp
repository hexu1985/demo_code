#include "sold_state.h"
#include "gumball_machine.h"
#include <iostream>

SoldState::SoldState(GumballMachine &gumballMachine): gumballMachine(gumballMachine) {
}
       
void SoldState::insertQuarter() {
    std::cout << "Please wait, we're already giving you a gumball" << "\n";
}

void SoldState::ejectQuarter() {
    std::cout << "Sorry, you already turned the crank" << "\n";
}

void SoldState::turnCrank() {
    std::cout << "Turning twice doesn't get you another gumball!" << "\n";
}

void SoldState::dispense() {
    gumballMachine.releaseBall();
    if (gumballMachine.getCount() > 0) {
        gumballMachine.setState(gumballMachine.getNoQuarterState());
    } else {
        std::cout << "Oops, out of gumballs!" << "\n";
        gumballMachine.setState(gumballMachine.getSoldOutState());
    }
}

std::string SoldState::toString() const {
    return "dispensing a gumball";
}
