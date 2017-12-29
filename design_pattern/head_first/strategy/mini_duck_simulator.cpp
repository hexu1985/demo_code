#include "mallard_duck.h"
#include "rubber_duck.h"
#include "decoy_duck.h"
#include "model_duck.h"
#include "fly_rocket_powered.h"

int main(int argc, char *argv[]) {

    MallardDuck mallard;
    RubberDuck  rubberDuckie;
    DecoyDuck   decoy;

    ModelDuck   model;

    mallard.performQuack();
    rubberDuckie.performQuack();
    decoy.performQuack();

    model.performFly(); 
    model.setFlyBehavior(std::make_shared<FlyRocketPowered>());
    model.performFly();

    return 0;
}
