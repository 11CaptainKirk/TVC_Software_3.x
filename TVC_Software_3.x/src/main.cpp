#include <Arduino.h>
#include "loop/system_state.hpp"
#include "loop/data_class.h"


SensorData data;


byte systemState = 0;
void setup()
{
  int y = data.rawEuler->x;
  int z = data.Euler.y;
  // put your setup code here, to run once:
}

void loop()
{
  // put your main code here, to run repeatedly:
  stateMachine(systemState);
}