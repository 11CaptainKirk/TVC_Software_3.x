#include <Arduino.h>
#include "loop/state_machine.hpp"
#include "loop/telemetry.h"
#include "setup/system_init.hpp"

Telemetry telemetry;

void setup()
{
  systemState = systemInit();
}

void loop()
{
  systemState = stateMachine(systemState);
}