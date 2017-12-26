#include "chocolate_boiler.h"

int main(int argc, char *argv[]) {
    ChocolateBoiler &boiler = ChocolateBoiler::getInstance();
    boiler.fill();
    boiler.boil();
    boiler.drain();

    // will return the existing instance
    ChocolateBoiler &boiler2 = ChocolateBoiler::getInstance();
    return 0;
}
