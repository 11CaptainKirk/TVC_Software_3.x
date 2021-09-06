#include <Arduino.h>
#include <system_state.h>
#include <SPI.h>
#include <Adafruit_BMP085.h>
#include <SimpleKalmanFilter.h>
#include <telemetry.h>

Adafruit_BMP085 bmp180;

SimpleKalmanFilter bmpKalmanFilter(1, 1, 0.1); // Set values for response of Kalman filter here.

SystemState bmp180x0Setup()
{
    Serial.println("Barometric Pressure Sensor #0 Test");
    Serial.println("");
    if (!bmp180.begin())
    {
        Serial.println("** BMP180 #0 is not detected **\t\t<<");
        SystemState stateBmp0 = ERROR_BARO;
        return stateBmp0;
    }
    return READY;
}
void bmp180x0Loop()
{
    // Set New Values to telemetry object.
    telemetry.bmp180.rawValues.pressure = bmp180.readPressure();
    telemetry.bmp180.rawValues.temperature = bmp180.readTemperature();
    telemetry.bmp180.rawValues.altitude = bmp180.readAltitude();

    telemetry.bmp180.processedValues.pressure = bmpKalmanFilter.updateEstimate(telemetry.bmp180.rawValues.pressure);       // Is this really needed ?
    telemetry.bmp180.processedValues.temperature = bmpKalmanFilter.updateEstimate(telemetry.bmp180.rawValues.temperature); // Is this really needed ?
    telemetry.bmp180.processedValues.altitude = bmpKalmanFilter.updateEstimate(telemetry.bmp180.rawValues.altitude);
}

SystemState bmp180_0(FunctionMode mode)
{
    if (mode == SETUP)
    {
        return bmp180x0Setup();
    }
    else if (mode == LOOP)
    {
        bmp180x0Loop();
        return DATA_OK;
    }
}
