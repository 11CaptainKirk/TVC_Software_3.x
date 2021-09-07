#include <Arduino.h>
#include <SD.h>


void csvHeaderPrint() {
    Serial.print(F("Milliseconds since power on"));
    Serial.print(F(","));
    Serial.print(F("Date/Time"));
    Serial.print(F(","));
    Serial.print(F("System Status"));
    Serial.print(F(","));
    Serial.print(F("Corrected Euler X"));
    Serial.print(F(","));
    Serial.print(F("Corrected Euler Y"));
    Serial.print(F(","));
    Serial.print(F("Corrected Euler Z"));


}