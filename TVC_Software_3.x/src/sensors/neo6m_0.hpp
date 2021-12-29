#include <TinyGPS++.h>
#include <Arduino.h>
#include <system_state.h>
#include <SPI.h>
#include <telemetry.h>

TinyGPSPlus gps;

void neo6mSetup()
{
    Serial1.begin(9600);
    Serial.println("NEO-6M GPS #0 Test");
    Serial.println("");
}

SystemState neo6mLoop()
{
    static bool gpsReady = false;
    while (Serial1.available() > 0)
        if (gps.encode(Serial1.read()))
        {
            while (!gpsReady && !gps.location.isValid())  // Add something to check if the location has not been valid in ~ 5 secs and throw error for warning beeps. 
            {
                return INITIALIZING; 
            }
            if (gps.location.isValid())
            {
                telemetry.neo6m.position.lattitude = gps.location.lat();
                telemetry.neo6m.position.longitude = gps.location.lng();
                telemetry.neo6m.position.altitude = gps.altitude.meters();
                telemetry.neo6m.misc.numSats = gps.satellites.value();
                telemetry.neo6m.misc.dataAge = gps.location.age();

                telemetry.neo6m.time.year = gps.date.year();
                telemetry.neo6m.time.month = gps.date.month();
                telemetry.neo6m.time.day = gps.date.day();
                telemetry.neo6m.time.hour = gps.time.hour();
                telemetry.neo6m.time.minute = gps.time.minute();
                telemetry.neo6m.time.second = gps.time.second();
                gpsReady = true;
                return READY;
            }
        }
    if (millis() > 5000 && gps.charsProcessed() < 10) // TODO: Problem because it takes longer to get through setup
    {
        Serial.println(F("** NEO-6M GPS ERROR **\t\t<<"));
        return ERROR_GPS;
    }
}

SystemState neo6m_0(FunctionMode mode)
{
    if (mode == SETUP)
    {
        neo6mSetup();
        return DATA_OK;
    }
    else if (mode == LOOP)
    {
        return neo6mLoop();
    }
}
