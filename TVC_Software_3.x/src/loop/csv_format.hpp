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
                    String(millis())                                 // MS since power on
            + "," + String(telemetry.utility.time.month)                // Current Date / Time 
            + "/" + String(telemetry.utility.time.day)    
            + "/" + String(telemetry.utility.time.year) 
            + " " + String(telemetry.utility.time.hour) 
            + ":" + String(telemetry.utility.time.minute) 
            + ":" + String(telemetry.utility.time.second) 
            + "," + String(systemState)                                 // Current system state
            + "," + String(telemetry.bno055_0.normalizedEuler.y)        // Normalized Eulers (corrected & zeroed)
            + "," + String(telemetry.bno055_0.normalizedEuler.z) 
            + "," + String(telemetry.bmp180.normalizedValues.altitude)   // Filtered Barometric altitude
            + "," + String(telemetry.bmp180.rawValues.temperature)      // Temperature
            + "," + String(telemetry.neo6m.position.lattitude, 6)          // GPS Coordinates
            + "," + String(telemetry.neo6m.position.longitude, 6)
            + "," + String(telemetry.neo6m.position.altitude)           // GPS Altitude
            + "," + String(telemetry.neo6m.misc.numSats)                // Number of Sattelite fixes
            + "," + String(telemetry.utility.home.pyro1Status)          // Pyro channel status
            + "," + String(telemetry.utility.home.pyro2Status)
            + "," + String(telemetry.bno055_0.rawAccel.x)               // Raw Acceleration Values
            + "," + String(telemetry.bno055_0.rawAccel.y)
            + "," + String(telemetry.bno055_0.rawAccel.z)
            + "," + String(telemetry.bno055_0.rawEuler.x)               // Raw Euler Angles
            + "," + String(telemetry.bno055_0.rawEuler.y)
            + "," + String(telemetry.bno055_0.rawEuler.z)          // Pyro channel status
            + "," + String(telemetry.utility.home.pyro2Status);
        return dataOut;
    }
};