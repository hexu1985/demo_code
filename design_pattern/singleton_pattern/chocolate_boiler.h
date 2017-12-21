#ifndef __chocolate_boiler_h
#define __chocolate_boiler_h

#include <iostream>

class ChocolateBoiler {
private:
    bool empty;
    bool boiled;
    static ChocolateBoiler *uniqueInstance;
  
    ChocolateBoiler() {
        empty = true;
        boiled = false;
    }

    ChocolateBoiler(const ChocolateBoiler &);
    void operator =(const ChocolateBoiler &);
  
public:
    static ChocolateBoiler &getInstance() {
        if (uniqueInstance == NULL) {
            std::cout << "Creating unique instance of Chocolate Boiler" << std::endl;
            uniqueInstance = new ChocolateBoiler;
        }
        std::cout << "Returning instance of Chocolate Boiler" << std::endl;
        return *uniqueInstance;
    }

    void fill() {
        if (isEmpty()) {
            empty = false;
            boiled = false;
            // fill the boiler with a milk/chocolate mixture
        }
    }
 
    void drain() {
        if (!isEmpty() && isBoiled()) {
            // drain the boiled milk and chocolate
            empty = true;
        }
    }
 
    void boil() {
        if (!isEmpty() && !isBoiled()) {
            // bring the contents to a boil
            boiled = true;
        }
    }
  
    bool isEmpty() {
        return empty;
    }
 
    bool isBoiled() {
        return boiled;
    }
};

#endif
