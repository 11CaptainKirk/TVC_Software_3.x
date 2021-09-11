#include <Arduino.h>
#include <SD.h>


void csvHeaderPrint() {
    Serial.print(F("Millis")); //
    Serial.print(F(","));
    Serial.print(F("Date/Time")); //
    Serial.print(F(","));
    Serial.print(F("System Status")); //
    Serial.print(F(","));
    Serial.print(F("Normalized Euler Y")); //
    Serial.print(F(","));
    Serial.print(F("Normalized Euler Z")); //
    Serial.print(F(","));
    Serial.print(F("Filtered Altitude")); //
    Serial.print(F(","));
    Serial.print(F("Temperature")); //
    Serial.print(F(","));
    Serial.print(F("Lattitude")); //
    Serial.print(F(","));
    Serial.print(F("Longitude")); //
    Serial.print(F(","));
    Serial.print(F("GPS Altitude")); //
    Serial.print(F(","));
    Serial.print(F("Sat Fix #")); //
    Serial.print(F(","));
    Serial.print(F("Pyro 1 Status"));  //
    Serial.print(F(","));
    Serial.print(F("Pyro 2 Status"));  //
    Serial.print(F(","));
    Serial.print(F("Raw Euler X"));
    Serial.print(F(","));
    Serial.print(F("Raw Euler Y")); 
    Serial.print(F(","));
    Serial.print(F("Raw Euler Z"));
    Serial.print(F(","));
    Serial.print(F("Corrected Euler X"));
    Serial.print(F(","));
    Serial.print(F("Corrected Euler Y"));
    Serial.print(F(","));
    Serial.print(F("Quaternion X"));
    Serial.print(F(","));
    Serial.print(F("Quaternion Y"));
    Serial.print(F(","));
    Serial.print(F("Quaternion Z")); 
    Serial.print(F(","));
    Serial.print(F("Quaternion W"));
    Serial.print(F(","));
    Serial.print(F("Gimbal Euler X"));
    Serial.print(F(","));
    Serial.print(F("Gimbal Euler Y"));
    Serial.print(F(","));
    Serial.print(F("Gimbal Euler Z"));
    Serial.print(F(","));
    Serial.print(F("Gimbal Quaternion X"));
    Serial.print(F(","));
    Serial.print(F("Gimbal Quaternion Y"));
    Serial.print(F(","));
    Serial.print(F("Gimbal Quaternion Z"));
    Serial.print(F(","));
    Serial.print(F("Gimbal Quaternion W"));
    Serial.print(F(","));
    Serial.print(F("Unfiltered Altitude"));
    Serial.print(F(","));
    Serial.print(F("Pressure"));
    Serial.print(F(","));
    Serial.print(F("PID Setpoint Y"));
    Serial.print(F(","));
    Serial.print(F("PID Setpoint Z"));
    Serial.print(F(","));
    Serial.print(F("Gimbal Home Y"));
    Serial.print(F(","));
    Serial.print(F("Gimbal Home Z"));
    Serial.print(F(","));
    Serial.print(F("PID Proportional"));
    Serial.print(F(","));
    Serial.print(F("PID Integral"));
    Serial.print(F(","));
    Serial.print(F("PID Derivative"));
    Serial.print(F(","));
    Serial.print(F("Kalman Meas. Uncertainty"));
    Serial.print(F(","));
    Serial.print(F("Kalman Est. Uncertainty"));
    Serial.print(F(","));
    Serial.print(F("Kalman Process Variance"));


}