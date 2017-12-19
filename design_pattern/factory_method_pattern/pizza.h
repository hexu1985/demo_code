#ifndef __pizza_h
#define __pizza_h

#include <vector>
#include <string>
#include <iostream>
#include <sstream>

class Pizza {
protected:
    std::string name;
    std::string dough;
    std::string sauce;
    std::vector<std::string> toppings;

public:
    virtual ~Pizza() {}

    void prepare() {
        std::cout << "Preparing " << name << "\n"
                << "Tossing dough..." << "\n"
                << "Adding sauce..." << "\n"
                << "Adding toppings: " << "\n";
        for (size_t i = 0; i < toppings.size(); i++) {
            std::cout << "   " << toppings.at(i) << "\n";
        }
    }

    void bake() {
        std::cout << "Bake for 25 minutes at 350" << std::endl;
    }

    virtual void cut() {
        std::cout << "Cutting the pizza into diagonal slices" << std::endl;
    }

    void box() {
        std::cout << "Place pizza in official PizzaStore box" << std::endl;
    }

    std::string getName() {
        return name;
    }

    std::string toString() {
        // code to display pizza name and ingredients
        std::ostringstream os;
        os << "---- " << name << " ----\n"
            << dough << "\n"
            << sauce << "\n";
        for (size_t i = 0; i < toppings.size(); i++) {
            os << toppings[i] << "\n";
        }
        return os.str();
    }
};

#endif
