#ifndef __beverage_h
#define __beverage_h

#include <string>

// 饮料
class Beverage {
private:
    std::string description = "Unknown Beverage";

public:
    Beverage() {}

    Beverage(const std::string description): description(description) {}
 
    virtual std::string getDescription() const {
        return description;
    }

    virtual double cost() const = 0;
};

#endif
