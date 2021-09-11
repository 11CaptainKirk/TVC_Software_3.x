#include <Arduino.h>
#include <system_state.h>

SystemState initStatus;

SystemState systemInit()
{
    initStatus = INITIALIZING;

    pinMode(telemetry.utility.gpio.buzzer, OUTPUT);         // Buzzer PinMode
    pinMode(telemetry.utility.gpio.led, OUTPUT);            // LED PinMode
    pinMode(telemetry.utility.gpio.button, INPUT_PULLUP);   // Button PinMode
    pinMode(telemetry.utility.gpio.pyro1, OUTPUT);          // Pyro Pin Mode
    pinMode(telemetry.utility.gpio.pyro2, OUTPUT);

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

    // Setup Servos
    servo(SETUP);

    return initStatus;
}