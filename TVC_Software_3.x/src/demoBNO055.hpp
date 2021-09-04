#include <Arduino.h>
#include <system_state.h>

// Maybe add return value to check for errors

void setup()
{
    // DO SETUP ACTIONS
}
void loop()
{
    // DO LOOP ACTIONS
}

void BNO055(FunctionMode mode)
{
    if (mode == SETUP)
    {
        setup();
    }
    else if (mode == LOOP)
    {
        loop();
    }
}
