#include <Arduino.h>
#include <system_state.h>
#include <Adafruit_BNO055.h>
#include <SPI.h>
#include <telemetry.h>
#include <PID_v1.h>

Adafruit_BNO055 bno055x0 = Adafruit_BNO055(55, 0x28); // Create IMU Object

PID PIDy(&telemetry.pid.input.y, &telemetry.pid.output.y, &telemetry.pid.terms.setpoint, telemetry.pid.terms.p, telemetry.pid.terms.i, telemetry.pid.terms.d, DIRECT); // PID Y //TODO: Add variables to PID values.
PID PIDz(&telemetry.pid.input.z, &telemetry.pid.output.z, &telemetry.pid.terms.setpoint, telemetry.pid.terms.p, telemetry.pid.terms.i, telemetry.pid.terms.d, DIRECT); // PID Z

SystemState bno055x0Setup() // Setup function runs during setup in main.
{
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
    // Set Values to telemetry object.
    telemetry.bno055_0.rawEuler.x = IMUreadingx0.orientation.x;
    telemetry.bno055_0.rawEuler.y = IMUreadingx0.orientation.y;
    telemetry.bno055_0.rawEuler.z = IMUreadingx0.orientation.z;

    telemetry.pid.input.y = telemetry.bno055_0.rawEuler.y;
    telemetry.pid.input.z = telemetry.bno055_0.rawEuler.z;

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