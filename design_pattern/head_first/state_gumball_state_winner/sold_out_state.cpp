#include "sold_out_state.h"
#include "gumball_machine.h"
#include <iostream>

SoldOutState::SoldOutState(GumballMachine &gumballMachine): gumballMachine(gumballMachine) {
}

void SoldOutState::insertQuarter() {
    std::cout << "You can't insert a quarter, the machine is sold out" << "\n";
}

void SoldOutState::ejectQuarter() {
    std::cout << "You can't eject, you haven't inserted a quarter yet" << "\n";
}

void SoldOutState::turnCrank() {
    std::cout << "You turned, but there are no gumballs" << "\n";
}

void SoldOutState::dispense() {
    std::cout << "No gumball dispensed" << "\n";
}

std::string SoldOutState::toString() const {
    return "sold out";
}
