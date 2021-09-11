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
    // Update Servo Locations
    if (telemetry.pid.output.y > 10)  // Update Y Servo
    {
        servoY.write(telemetry.utility.home.gimbalOffsetY + telemetry.utility.home.gimbalMaxY);
    }
    else if (telemetry.pid.output.y < -10)
    {
        servoY.write(telemetry.utility.home.gimbalOffsetY - telemetry.utility.home.gimbalMaxY);
    }
    else
    {
        servoY.write(telemetry.utility.home.gimbalOffsetY + telemetry.pid.output.y);
    }

     if (telemetry.pid.output.z > 10){  // Update Z Servo 
        servoZ.write(telemetry.utility.home.gimbalOffsetZ + telemetry.utility.home.gimbalMaxZ);
    }
    else if (telemetry.pid.output.z < -10){
        servoZ.write(telemetry.utility.home.gimbalOffsetZ - telemetry.utility.home.gimbalMaxZ);
    }
    else {
        servoZ.write(telemetry.utility.home.gimbalOffsetZ + telemetry.pid.output.z);
    }
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
