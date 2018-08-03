#include <memory>
#include <iostream>
#include "mallar_duck.h"
#include "wild_turkey.h"
#include "turkey_adapter.h"

void testDuck(std::shared_ptr<Duck> duck) {
    duck->quack();
    duck->fly();
}

int main(int argc, char *argv[]) {
    auto duck = std::make_shared<MallardDuck>();

    auto turkey = std::make_shared<WildTurkey>();
    auto turkeyAdapter = std::make_shared<TurkeyAdapter>(turkey);

    std::cout << "The Turkey says...\n";
    turkey->gobble();
    turkey->fly();

    std::cout << "\nThe Duck says...\n";
    testDuck(duck);

    std::cout << "\nThe TurkeyAdapter says...\n";
    testDuck(turkeyAdapter);
}

