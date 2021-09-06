#include <Arduino.h>
#include <PWMServo.h>
#include <telemetry.h>
#ifndef SERVO_INIT_HPP
#define SERVO_INIT_HPP

PWMServo servoY;
PWMServo servoZ;

void servoInit()
{

    servoY.write(telemetry.utility.home.gimbalOffsetY + (telemetry.utility.home.gimbalMaxY)); // Y Plus
    delay(400);
    servoY.write(telemetry.utility.home.gimbalOffsetY - (telemetry.utility.home.gimbalMaxY)); // Y Minus
    delay(400);
    servoY.write(telemetry.utility.home.gimbalOffsetY);                                       // Y Reset
    servoZ.write(telemetry.utility.home.gimbalOffsetZ + (telemetry.utility.home.gimbalMaxZ)); // Z Plus
    delay(400);
    servoZ.write(telemetry.utility.home.gimbalOffsetZ - (telemetry.utility.home.gimbalMaxZ)); // Z Minus
    delay(400);
    servoZ.write(telemetry.utility.home.gimbalOffsetZ); // Z Reset
}
#endif