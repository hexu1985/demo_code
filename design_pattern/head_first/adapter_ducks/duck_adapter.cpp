#include "duck_adapter.h"
#include <chrono>

DuckAdapter::DuckAdapter(std::shared_ptr<Duck> duck) {
    this->duck = duck;
    unsigned seed1 = std::chrono::system_clock::now().time_since_epoch().count();
    rand = std::make_shared<std::minstd_rand0>(seed1);
}

void DuckAdapter::gobble() {
    duck->quack();
}

void DuckAdapter::fly() {
    if ((*rand)() % 5 == 0) {
        duck->fly();
    }
}

