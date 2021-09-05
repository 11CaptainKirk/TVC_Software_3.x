#include <Arduino.h>
#include <system_state.h>

SystemState initStatus;

SystemState systemInit()
{
    initStatus = INITIALIZING;

    if (bno055_0(SETUP) == READY)
    {
        initStatus = GROUND_IDLE;
    }

    return initStatus;
}