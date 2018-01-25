#include <memory>

#include "simple_remote_control.h"
#include "light.h"
#include "garage_door.h"
#include "light_on_command.h"
#include "garage_door_open_command.h"

int main(int argc, char *argv[]) {
    SimpleRemoteControl remote;
    auto light = std::make_shared<Light>();
    auto garageDoor = std::make_shared<GarageDoor>();
    auto lightOn = std::make_unique<LightOnCommand>(light);
    auto garageOpen = std::make_unique<GarageDoorOpenCommand>(garageDoor);

    remote.setCommand(std::move(lightOn));
    remote.buttonWasPressed();
    remote.setCommand(std::move(garageOpen));
    remote.buttonWasPressed();

    return 0;
}
