#include "no_quarter_state.h"
#include "gumball_machine.h"
#include <iostream>

NoQuarterState::NoQuarterState(GumballMachine &gumballMachine): gumballMachine(gumballMachine) {
}

void NoQuarterState::insertQuarter() {
    std::cout << "You inserted a quarter" << "\n";
    gumballMachine.setState(gumballMachine.getHasQuarterState());
}

void NoQuarterState::ejectQuarter() {
    std::cout << "You haven't inserted a quarter" << "\n";
}

void NoQuarterState::turnCrank() {
    std::cout << "You turned, but there's no quarter" << "\n";
}

void NoQuarterState::dispense() {
    std::cout << "You need to pay first" << "\n";
}

std::string NoQuarterState::toString() const {
    return "waiting for quarter";
}
