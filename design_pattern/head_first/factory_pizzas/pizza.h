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

    std::string getName() {
        return name;
    }

    void prepare() {
        std::cout << "Preparing " << name << std::endl;
    }

    void bake() {
        std::cout << "Baking " << name << std::endl;
    }

    void cut() {
        std::cout << "Cutting " << name << std::endl;
    }

    void box() {
        std::cout << "Boxing " << name << std::endl;
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
