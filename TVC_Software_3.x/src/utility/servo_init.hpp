#include <Arduino.h>
#include <PWMServo.h>
#include <telemetry.h>
#ifndef SERVO_INIT_HPP
#define SERVO_INIT_HPP

PWMServo servoY;
PWMServo servoZ;

void servoInit()
{

    int testAngle = 10;

    servoY.write(telemetry.utility.home.gimbalOffsetY + (testAngle)); // Y Plus
    delay(400);
    servoY.write(telemetry.utility.home.gimbalOffsetY - (testAngle)); // Y Minus
    delay(400);
    servoY.write(telemetry.utility.home.gimbalOffsetY); // Y Reset
    servoZ.write(telemetry.utility.home.gimbalOffsetZ + (testAngle)); // Z Plus
    delay(400);
    servoZ.write(telemetry.utility.home.gimbalOffsetZ - (testAngle)); // Z Minus
    delay(400);
    servoZ.write(telemetry.utility.home.gimbalOffsetZ); // Z Reset
}
#endif