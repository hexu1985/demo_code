#include <memory>
#include "mallard_duck.h"
#include "duck.h"
#include "model_duck.h"
#include "fly_rocket_powered.h"

int main(int argc, char *argv[]) {

    std::unique_ptr<Duck> mallard(new MallardDuck);
    mallard->performQuack();
    mallard->performFly();

    std::unique_ptr<Duck> model(new ModelDuck);
    model->performFly();
    model->setFlyBehavior(std::make_shared<FlyRocketPowered>());
    model->performFly();

    return 0;
}
