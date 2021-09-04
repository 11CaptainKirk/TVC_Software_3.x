#include <Arduino.h>
#include "loop/system_state.hpp"
#include "loop/data_class.h"

class TestClass
{
public:
  int x;
};

byte systemState = 0;

void setup()
{
  // put your setup code here, to run once:
}

void loop()
{
  // put your main code here, to run repeatedly:
  stateMachine(systemState);
}