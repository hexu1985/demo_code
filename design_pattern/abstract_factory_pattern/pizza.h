#ifndef __pizza_h
#define __pizza_h

#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include <sstream>

#include "dough.h"
#include "sauce.h"
#include "veggies.h"
#include "cheese.h"
#include "pepperoni.h"
#include "clams.h"

class Pizza {
protected:
    std::string name;

    Dough *dough = 0;
    Sauce *sauce = 0;
    std::vector<Veggies *> veggies;
    Cheese *cheese = 0;
    Pepperoni *pepperoni = 0;
    Clams *clam = 0;

public:
    virtual ~Pizza() {
        delete dough;
        delete sauce;
        for (auto veggie: veggies)
            delete veggie;
        delete cheese;
        delete pepperoni;
        delete clam;
    }

    virtual void prepare() = 0;

    void bake() {
        std::cout << "Bake for 25 minutes at 350" << std::endl;
    }

    void cut() {
        std::cout << "Cutting the pizza into diagonal slices" << std::endl;
    }

    void box() {
        std::cout << "Place pizza in official PizzaStore box" << std::endl;
    }

    void setName(const std::string &name) {
        this->name = name;
    }

    std::string getName() {
        return name;
    }

    std::string toString() {
        // code to display pizza name and ingredients
        std::ostringstream os;
        os << "---- " << name << " ----\n";
        if (dough) {
            os << dough->toString() << "\n";
        }
        if (sauce) {
            os << sauce->toString() << "\n";
        }
        if (cheese) {
            os << cheese->toString() << "\n";
        }
        if (!veggies.empty()) {
            for (size_t i = 0; i < veggies.size(); i++) {
                os << veggies[i]->toString();
                if (i < veggies.size()-1) {
                    os << ", ";
                }
            }
            os << "\n";
        }
        if (clam) {
            os << clam->toString() << "\n";
        }
        if (pepperoni) {
            os << pepperoni->toString() << "\n";
        }
        return os.str();
    }
};

#endif
