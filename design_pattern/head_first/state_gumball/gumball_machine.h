#ifndef __gumball_machine_h
#define __gumball_machine_h

#include <string>
#include <iostream>
#include <sstream>

class GumballMachine {
public:  
    static const int SOLD_OUT = 0;
    static const int NO_QUARTER = 1;
    static const int HAS_QUARTER = 2;
    static const int SOLD = 3;

private:
    int state = SOLD_OUT;
    int count = 0;

public:
    GumballMachine(int count) {
        this->count = count;
        if (count > 0) {
            state = NO_QUARTER;
        }
    }

    void insertQuarter() {
        if (state == HAS_QUARTER) {
            std::cout << "You can't insert another quarter" << "\n";
        } else if (state == NO_QUARTER) {
            state = HAS_QUARTER;
            std::cout << "You inserted a quarter" << "\n";
        } else if (state == SOLD_OUT) {
            std::cout << "You can't insert a quarter, the machine is sold out" << "\n";
        } else if (state == SOLD) {
            std::cout << "Please wait, we're already giving you a gumball" << "\n";
        }
    }

    void ejectQuarter() {
        if (state == HAS_QUARTER) {
            std::cout << "Quarter returned" << "\n";
            state = NO_QUARTER;
        } else if (state == NO_QUARTER) {
            std::cout << "You haven't inserted a quarter" << "\n";
        } else if (state == SOLD) {
            std::cout << "Sorry, you already turned the crank" << "\n";
        } else if (state == SOLD_OUT) {
            std::cout << "You can't eject, you haven't inserted a quarter yet" << "\n";
        }
    }

    void turnCrank() {
        if (state == SOLD) {
            std::cout << "Turning twice doesn't get you another gumball!" << "\n";
        } else if (state == NO_QUARTER) {
            std::cout << "You turned but there's no quarter" << "\n";
        } else if (state == SOLD_OUT) {
            std::cout << "You turned, but there are no gumballs" << "\n";
        } else if (state == HAS_QUARTER) {
            std::cout << "You turned..." << "\n";
            state = SOLD;
            dispense();
        }
    }

    void dispense() {
        if (state == SOLD) {
            std::cout << "A gumball comes rolling out the slot" << "\n";
            count = count - 1;
            if (count == 0) {
                std::cout << "Oops, out of gumballs!" << "\n";
                state = SOLD_OUT;
            } else {
                state = NO_QUARTER;
            }
        } else if (state == NO_QUARTER) {
            std::cout << "You need to pay first" << "\n";
        } else if (state == SOLD_OUT) {
            std::cout << "No gumball dispensed" << "\n";
        } else if (state == HAS_QUARTER) {
            std::cout << "No gumball dispensed" << "\n";
        }
    }

    void refill(int numGumBalls) {
        this->count = numGumBalls;
        state = NO_QUARTER;
    }

    std::string toString() const {
        std::string result;
        result += "\nMighty Gumball, Inc.";
        result += "\nJava-enabled Standing Gumball Model #2004\n";
        result += "Inventory: " + std::to_string(count) + " gumball";
        if (count != 1) {
            result += "s";
        }
        result += "\nMachine is ";
        if (state == SOLD_OUT) {
            result += "sold out";
        } else if (state == NO_QUARTER) {
            result += "waiting for quarter";
        } else if (state == HAS_QUARTER) {
            result += "waiting for turn of crank";
        } else if (state == SOLD) {
            result += "delivering a gumball";
        }
        result += "\n";
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
