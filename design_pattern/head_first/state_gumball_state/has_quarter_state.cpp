#include "sold_out_state.h"
#include "gumball_machine.h"
#include <iostream>

HasQuarterState::HasQuarterState(GumballMachine &gumballMachine): gumballMachine(gumballMachine) {
}

void HasQuarterState::insertQuarter() {
    std::cout << "You can't insert another quarter" << "\n";
}

void HasQuarterState::ejectQuarter() {
    std::cout << "Quarter returned" << "\n";
    gumballMachine.setState(gumballMachine.getNoQuarterState());
}

void HasQuarterState::turnCrank() {
    std::cout << "You turned..." << "\n";
    gumballMachine.setState(gumballMachine.getSoldState());
}

void HasQuarterState::dispense() {
    std::cout << "No gumball dispensed" << "\n";
}

std::string HasQuarterState::toString() const {
    return "waiting for turn of crank";
}
