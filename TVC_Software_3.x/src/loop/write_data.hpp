#include <Arduino.h>
#include <system_state.h>
#include <SD.h>
#include <loop/csv_format.hpp>

CSV_Format csv;

void writeData()
{
    File logFile = SD.open("flightData2.txt", FILE_WRITE);
    logFile.println(csv.dataStringCSV());
    logFile.close();
    //Serial.println(csv.dataStringCSV());
    Serial.print(telemetry.bno055_0.rawAccel.x);
    Serial.print("\t");
    Serial.println(telemetry.bno055_0.rawEuler.x);
}
