#include <Arduino.h>
#include "loop/state_machine.hpp"
#include "telemetry.h"
#include "setup/system_init.hpp"

void setup()
{
  systemState = systemInit();
}

void loop()
{
  stateMachine();
}