// TODO: FIX PERMISSIONS; Classes should be nested inside of master class not struct. (Problem with pointers for access)
#ifndef TELEMETRY_H
#define TELEMETRY_H

class IMU
{
    struct Axes
    {
        double x;
        double y;
        double z;
        double w;
    };

public:
    Axes rawEuler;
    Axes rawAccel;
    Axes processedEuler;
    Axes rawQuaternion;
    Axes processedQuaternion;
};

class PIDdata
{
    struct PIDoutput
    {
        double y;
        double z;
    };
    struct PIDterms
    {
        const float p = 1;
        const float i = 0;
        const float d = 0;
        double setpoint = 0;
    };

public:
    PIDoutput output;
    PIDoutput input;
    PIDterms terms;
};

class Barometer
{
    struct BarometerValues
    {
        double pressure;
        double temperature;
        double altitude;
    };

public:
    BarometerValues rawValues;
    BarometerValues processedValues;
};

class GPS
{
    struct GPSPosition
    {
        double lattitude;
        double longitude;
        double altitude;
    };
    struct GPSTime
    {
        short year;
        byte month;
        byte day;
        byte hour;
        byte minute;
        byte second;
    };
    struct GPSMisc
    {
        short numSats;
        short dataAge;
    };

public:
    GPSPosition position;
    GPSTime time;
    GPSMisc misc;
};

class Utility
{
    struct Pinouts // Pin numbers for physical hardware.
    {
        const int button = 39;
        const int led = 35;
        const int buzzer = 23;
        const int servoYpin = 4;
        const int servoZpin = 5;
    };
    struct Default // Default values for system
    {
        float gimbalOffsetY = 83;
        float gimbalOffsetZ = 84;
        float gimbalMaxY = 10;
        float gimbalMaxZ = 10;
        float startAltitude;
    };

public:
    Pinouts gpio;
    Default home;
};

struct Telemetry
{
    IMU bno055_0;
    IMU bno055_1;
    Barometer bmp180;
    GPS neo6m;
    PIDdata pid;
    Utility utility;
};

Telemetry telemetry;
SystemState systemState;

#endif