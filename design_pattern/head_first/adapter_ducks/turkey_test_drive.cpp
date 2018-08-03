#include <iostream>
#include <memory>
#include "mallar_duck.h"
#include "duck_adapter.h"

int main(int argc, char *argv[]) {
    auto duck = std::make_shared<MallardDuck>();
    auto duckAdapter = std::make_shared<DuckAdapter>(duck);

    for(int i=0;i<10;i++) {
        std::cout << "The DuckAdapter says...\n";
        duckAdapter->gobble();
        duckAdapter->fly();
    }

    return 0;
}
