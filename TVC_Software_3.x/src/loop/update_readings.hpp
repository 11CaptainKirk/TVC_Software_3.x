#include <sensors/bno055_0.hpp>
#include <sensors/bno055_1.hpp>
#include <sensors/bmp180_0.hpp>
#include <sensors/neo6m_0.hpp>
#ifndef UPDATE_READINGS_HPP
#define UPDATE_READINGS_HPP

SystemState readSensors()
{
    bno055_0(LOOP);
    bno055_1(LOOP);
    bmp180_0(LOOP);

    if (systemState == INITIALIZING && neo6m_0(LOOP) == READY)
    {
        return GROUND_IDLE;
    };
    if (systemState == GROUND_IDLE && neo6m_0(LOOP) == INITIALIZING)
    {
        return INITIALIZING;
    };
}
#endif