#include <Arduino.h>
#include <system_state.h>
#include <Adafruit_BNO055.h>
#include <SPI.h>
#include <telemetry.h>
#include <PID_v1.h>
#include <utility/quat_correct.hpp>

Adafruit_BNO055 bno055x0 = Adafruit_BNO055(55, 0x28); // Create IMU Object

PID PIDy(&telemetry.pid.input.y, &telemetry.pid.output.y, &telemetry.pid.terms.setpoint, telemetry.pid.terms.p, telemetry.pid.terms.i, telemetry.pid.terms.d, DIRECT); // PID Y //TODO: Add variables to PID values.
PID PIDz(&telemetry.pid.input.z, &telemetry.pid.output.z, &telemetry.pid.terms.setpoint, telemetry.pid.terms.p, telemetry.pid.terms.i, telemetry.pid.terms.d, DIRECT); // PID Z

QuatCorrect correctedEuler;

SystemState bno055x0Setup() // Setup function runs during setup in main.
{
    // Setup PID
    PIDy.SetMode(AUTOMATIC); // Turn PID on
    PIDz.SetMode(AUTOMATIC);
    PIDy.SetOutputLimits(-255, 255);
    PIDz.SetOutputLimits(-255, 255); // Allow Negative Outputs
    PIDy.SetSampleTime(25);
    PIDz.SetSampleTime(25); // Increase update frequency (default 200)

    // Setup IMU
    Serial.println("Orientation Sensor #0 Test");
    Serial.println("");
    if (!bno055x0.begin())
    {
        Serial.print("** BNO055 #0 is not detected **\t\t<<");
        SystemState stateBno0 = ERROR_IMU0;
        return stateBno0;
    }
    //delay(1000); //TODO: Why this delay?
    bno055x0.setExtCrystalUse(true);
    return READY;
}
void bno055x0Loop() // Loop function runs during loop in main.
{
    // Update Data
    sensors_event_t IMUreadingx0;
    bno055x0.getEvent(&IMUreadingx0);

    imu::Quaternion quat = bno055x0.getQuat();
    // Set Values to telemetry object.
    telemetry.bno055_0.rawEuler.x = IMUreadingx0.orientation.x;  // Get orientation readings (Euler [not usable because of gimbal lock])
    telemetry.bno055_0.rawEuler.y = IMUreadingx0.orientation.y;
    telemetry.bno055_0.rawEuler.z = IMUreadingx0.orientation.z;

    telemetry.bno055_0.rawAccel.x = IMUreadingx0.acceleration.x; // Get acceleration Readings
    telemetry.bno055_0.rawAccel.y = IMUreadingx0.acceleration.y;
    telemetry.bno055_0.rawAccel.z = IMUreadingx0.acceleration.z;

    telemetry.bno055_0.rawQuaternion.x = quat.x(); 
    telemetry.bno055_0.rawQuaternion.y = quat.y();
    telemetry.bno055_0.rawQuaternion.z = quat.z();
    telemetry.bno055_0.rawQuaternion.w = quat.w();


    QuatCorrect::Quat4d qx;   // Created redundant representation because of type (Can be fixed later)
    qx.x = telemetry.bno055_0.rawQuaternion.x;
    qx.y = telemetry.bno055_0.rawQuaternion.y;
    qx.z = telemetry.bno055_0.rawQuaternion.z;
    qx.w = telemetry.bno055_0.rawQuaternion.w;

    correctedEuler.correctEuler(qx);


    telemetry.bno055_0.normalizedEuler.y = telemetry.bno055_0.processedEuler.x - telemetry.utility.home.startY; // Starting angle when system is initialized is subtracted to make zero the point of interest.
    telemetry.bno055_0.normalizedEuler.z = telemetry.bno055_0.processedEuler.y - telemetry.utility.home.startZ; //  ? X is used because the reference coordinate system for the rocket is not aligned with that of the IMU

    telemetry.pid.input.y = telemetry.bno055_0.normalizedEuler.y; // PID inputs set to normalized (corrected & zeroed) Eulers.
    telemetry.pid.input.z = telemetry.bno055_0.normalizedEuler.z; // Can be removed and variable direct from IMU can be used if memory is an issue.


    PIDy.Compute();
    PIDz.Compute();
}

SystemState bno055_0(FunctionMode mode)
{
    if (mode == SETUP)
    {
        return bno055x0Setup();
    }
    else if (mode == LOOP)
    {
        bno055x0Loop();
        return DATA_OK;
    }
}
