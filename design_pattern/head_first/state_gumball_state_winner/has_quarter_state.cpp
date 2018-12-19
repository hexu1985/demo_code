#include "sold_out_state.h"
#include "gumball_machine.h"
#include <iostream>
#include <ctime>

HasQuarterState::HasQuarterState(GumballMachine &gumballMachine): 
    dre((unsigned int)time(0)), di(0, 10), 
    gumballMachine(gumballMachine) {
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
    int winner = di(dre);   // get next random int in [0, 10]
//    std::cout << "winner is " << winner << "\n";
    if ((winner == 0) && (gumballMachine.getCount() > 1)) {
        gumballMachine.setState(gumballMachine.getWinnerState());
    } else {
        gumballMachine.setState(gumballMachine.getSoldState());
    }
}

void HasQuarterState::dispense() {
    std::cout << "No gumball dispensed" << "\n";
}

std::string HasQuarterState::toString() const {
    return "waiting for turn of crank";
}
