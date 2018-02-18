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
    auto lightOn = std::make_shared<LightOnCommand>(light);
    auto garageOpen = std::make_shared<GarageDoorOpenCommand>(garageDoor);

    remote.setCommand(lightOn);
    remote.buttonWasPressed();
    remote.setCommand(garageOpen);
    remote.buttonWasPressed();

    return 0;
}
