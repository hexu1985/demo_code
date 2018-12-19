#include "winner_state.h"
#include "gumball_machine.h"
#include <iostream>

WinnerState::WinnerState(GumballMachine &gumballMachine): gumballMachine(gumballMachine) {
}
       
void WinnerState::insertQuarter() {
    std::cout << "Please wait, we're already giving you a Gumball" << "\n";
}

void WinnerState::ejectQuarter() {
    std::cout << "Please wait, we're already giving you a Gumball" << "\n";
}

void WinnerState::turnCrank() {
    std::cout << "Turning again doesn't get you another gumball!" << "\n";
}

void WinnerState::dispense() {
    std::cout << "YOU'RE A WINNER! You get two gumballs for your quarter" << "\n";
    gumballMachine.releaseBall();
    if (gumballMachine.getCount() == 0) {
        gumballMachine.setState(gumballMachine.getSoldOutState());
    } else {
        gumballMachine.releaseBall();
        if (gumballMachine.getCount() > 0) {
            gumballMachine.setState(gumballMachine.getNoQuarterState());
        } else {
            std::cout << "Oops, out of gumballs!" << "\n";
            gumballMachine.setState(gumballMachine.getSoldOutState());
        }
    }
}

std::string WinnerState::toString() const {
    return "despensing two gumballs for your quarter, because YOU'RE A WINNER!";
}
