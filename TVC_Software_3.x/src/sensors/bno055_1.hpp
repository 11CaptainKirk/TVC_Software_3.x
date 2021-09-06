#include <Arduino.h>
#include <system_state.h>
#include <Adafruit_BNO055.h>
#include <SPI.h>
#include <telemetry.h>

Adafruit_BNO055 bno055x1 = Adafruit_BNO055(55, 0x29); // Create IMU Object

SystemState bno055x1Setup() // TODO Implement class with private functions so these ridiculous function names are not needed.
{

    Serial.println("Orientation Sensor #1 Test");
    Serial.println("");
    if (!bno055x1.begin())
    {
        Serial.print("** BNO055 #1 is not detected **\t\t<<");
        SystemState stateBno1 = ERROR_IMU1;
        return stateBno1;
    }
    delay(1000); //TODO: Why this delay?
    bno055x1.setExtCrystalUse(true);
    return READY;
}
void bno055x1Loop()
{
    // Update Data
    sensors_event_t IMUreadingx1;
    bno055x1.getEvent(&IMUreadingx1);
    // Set Values to telemetry object.
    telemetry.bno055_1.rawEuler.x = IMUreadingx1.orientation.x;
    telemetry.bno055_1.rawEuler.y = IMUreadingx1.orientation.y;
    telemetry.bno055_1.rawEuler.z = IMUreadingx1.orientation.z;
}

SystemState bno055_1(FunctionMode mode)
{
    if (mode == SETUP)
    {
        bno055x1Setup();
    }
    else if (mode == LOOP)
    {
        bno055x1Loop();
        return DATA_OK;
    }
}
