#ifndef __duck_h
#define __duck_h

#include <memory>
#include <iostream>

#include "fly_behavior.h"
#include "quack_behavior.h"

class Duck {
protected:
    std::shared_ptr<FlyBehavior> flyBehavior;
    std::shared_ptr<QuackBehavior> quackBehavior;

public: 
    Duck() {
    }

    void setFlyBehavior(std::shared_ptr<FlyBehavior> fb) {
        flyBehavior = fb;
    }

    void setQuackBehavior(std::shared_ptr<QuackBehavior> qb) {
        quackBehavior = qb;
    }

    virtual void display() = 0;

    void performFly() {
        flyBehavior->fly();
    }

    void performQuack() {
        quackBehavior->quack();
    }

    void swim() {
        std::cout << "All ducks float, even decoys!\n";
    }
};

#endif
