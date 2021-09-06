#include <Arduino.h>
#include <system_state.h>
#include <telemetry.h>

class CSV_Format
{

    double *IMU0rX = &telemetry.bno055_0.rawEuler.x;
    double *IMU0rY = &telemetry.bno055_0.rawEuler.y;
    double *IMU0rZ = &telemetry.bno055_0.rawEuler.z;

    double *IMU0pX = &telemetry.bno055_0.processedEuler.x;
    double *IMU0pY = &telemetry.bno055_0.processedEuler.y;
    double *IMU0pZ = &telemetry.bno055_0.processedEuler.z;

    double *BNO0rA = &telemetry.bmp180.rawValues.altitude;
    double *BNO0pA = &telemetry.bmp180.processedValues.altitude;

public:
    String dataStringCSV()
    {
        String dataOut =
                    String(*IMU0rX, 4) 
            + "," + String(*IMU0rY, 4) 
            + "," + String(*IMU0rZ, 4) 
            + "," + String(*IMU0pX, 4) 
            + "," + String(*IMU0pY, 4) 
            + "," + String(*IMU0pZ, 4) 
            + "," + String(*BNO0rA, 4) 
            + "," + String(*BNO0pA, 4) 
            + "," + String(telemetry.neo6m.position.lattitude, 4) 
            + "," + String(telemetry.neo6m.position.longitude, 4) 
            + "," + String(systemState);
        return dataOut;
    }
};