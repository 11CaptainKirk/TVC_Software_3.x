#include <Arduino.h>
#include <system_state.h>


SystemState initStatus;

SystemState systemInit()
{
    initStatus = INITIALIZING;

    return initStatus;
}