#include "gumball_machine.h"

int main(int argc, char *argv[]) {
    GumballMachine gumballMachine(5);

    std::cout << gumballMachine << std::endl;

    gumballMachine.insertQuarter();
    gumballMachine.turnCrank();

    std::cout << gumballMachine << std::endl;

    gumballMachine.insertQuarter();
    gumballMachine.turnCrank();
    gumballMachine.insertQuarter();
    gumballMachine.turnCrank();

    std::cout << gumballMachine << std::endl;

    return 0;
}
