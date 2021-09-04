// TODO: FIX PERMISSIONS; Classes should be nested inside of master class not struct. (Problem with pointers for access)
#ifndef TELEMETRY_H
#define TELEMETRY_H

class IMU
{
    struct Axes
    {
        float x;
        float y;
        float z;
        float w;
    };

public:
    Axes rawEuler;
    Axes processedEuler;
    Axes rawQuaternion;
    Axes processedQuaternion;
};

class Barometer
{
    struct BarometerValues
    {
        float pressure;
        float temperature;
        float altitude;
    };

public:
    BarometerValues rawValues;
    BarometerValues processedValues;
};

class GPS
{
    struct GPSPosition
    {
        float lattitude;
        float longitude;
        float altitude;
    };
    struct GPSTime
    {
        float year;
        float month;
        float day;
        float hour;
        float minute;
        float second;
    };

public:
    GPSPosition position;
    GPSTime time;
};

struct Telemetry
{
    IMU bno055_0;
    IMU bno055_1;
    Barometer bmp180;
    GPS neo6m;
};

#endif