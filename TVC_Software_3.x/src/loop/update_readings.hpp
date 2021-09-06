#include <sensors/bno055_0.hpp>
#include <sensors/bno055_1.hpp>
#include <sensors/bmp180_0.hpp>
#ifndef UPDATE_READINGS_HPP
#define UPDATE_READINGS_HPP

void readSensors()
{
    bno055_0(LOOP);
    bno055_1(LOOP);
    bmp180_0(LOOP);
}
#endif