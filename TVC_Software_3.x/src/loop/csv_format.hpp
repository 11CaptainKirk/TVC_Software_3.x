#include <Arduino.h>
#include <system_state.h>
#include <telemetry.h>

class CSV_Format
{

    double *IMU0rX = &telemetry.bno055_0.rawEuler.x;
    double *IMU0rY = &telemetry.bno055_0.rawEuler.y;
    double *IMU0rZ = &telemetry.bno055_0.rawEuler.z;

    double *IMU1rX = &telemetry.bno055_1.rawEuler.x;
    double *IMU1rY = &telemetry.bno055_1.rawEuler.y;
    double *IMU1rZ = &telemetry.bno055_1.rawEuler.z;

    double *BNO0rA = &telemetry.bmp180.rawValues.altitude;
    double *BNO0pA = &telemetry.bmp180.processedValues.altitude;

public:
    String dataStringCSV()
    {
        String dataOut =
            String(*IMU0rX, 4) + "," + String(*IMU0rY, 4) + "," + String(*IMU0rZ, 4) + "," + String(*IMU1rX, 4) + "," + String(*IMU1rY, 4) + "," + String(*IMU1rZ, 4) + "," + String(*BNO0rA, 4) + "," + String(*BNO0pA, 4);
        return dataOut;
    }
};