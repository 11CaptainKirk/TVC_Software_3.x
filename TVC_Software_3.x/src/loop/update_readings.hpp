#include <bno055_0.hpp>
#ifndef UPDATE_READINGS_HPP
#define UPDATE_READINGS_HPP

void readSensors()
{
    bno055_0(LOOP);
}
#endif