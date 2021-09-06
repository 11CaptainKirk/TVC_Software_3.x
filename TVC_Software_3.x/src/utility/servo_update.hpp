#include <Arduino.h>
#include <system_state.h>
#include <SPI.h>
#include <Adafruit_BMP085.h>
#include <SimpleKalmanFilter.h>
#include <telemetry.h>
#include <utility/servo_init.hpp>


SystemState servoSetup()
{

    servoY.attach(telemetry.utility.gpio.servoYpin);
    servoZ.attach(telemetry.utility.gpio.servoZpin);

    Serial.println("Servo X Test, Servo Y Test"); // TODO make F print
    Serial.println("");

    servoInit();


    return READY;
}
void servoLoop()
{
    // Set New Values to telemetry object.
}

SystemState servo(FunctionMode mode)
{
    if (mode == SETUP)
    {
        return servoSetup();
    }
    else if (mode == LOOP)
    {
        servoLoop();
        return DATA_OK;
    }
}
