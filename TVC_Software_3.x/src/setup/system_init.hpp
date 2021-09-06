#include <Arduino.h>
#include <system_state.h>

SystemState initStatus;

SystemState systemInit()
{
    initStatus = INITIALIZING;

    pinMode(23, OUTPUT);
    pinMode(35, OUTPUT);

    Serial.begin(115200);

    // Setup bno055_0 and check for errors.
    initStatus = bno055_0(SETUP);
    if (initStatus == READY)
    {
        initStatus = GROUND_IDLE;
    }
    else
        return initStatus;
    //
    // Setup bno055_0 and check for errors.
    initStatus = bno055_1(SETUP);
    if (initStatus == READY)
    {
        initStatus = GROUND_IDLE;
    }
    else
        return initStatus;
    //
    // Setup bmp180_0 and check for errors.
    initStatus = bmp180_0(SETUP);
    if (initStatus == READY)
    {
        initStatus = GROUND_IDLE;
    }
    else
        return initStatus;
    //
    // Setup SD Card and check for errors.
    if (!SD.begin(BUILTIN_SDCARD))
    {
        initStatus = ERROR_SD;
        return initStatus;
    }
    else
        initStatus = GROUND_IDLE;
    //

    // Setup GPS
    neo6m_0(SETUP);
    //


    return initStatus;
}