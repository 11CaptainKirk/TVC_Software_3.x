#include <Arduino.h>

static void smartPulseLED(int pin, unsigned int onInterval_0, unsigned int offInterval_0, int numPulses = -1)
{
    static int prevTime = 0;
    static int pulseState = LOW;
    static int elapsedPulses = 0;
    if ((elapsedPulses < numPulses) || (numPulses == -1))
    {
        if ((pulseState == HIGH) && (millis() - prevTime >= onInterval_0))
        {
            pulseState = LOW;
            prevTime = millis();
            elapsedPulses++;
        }
        if ((pulseState == LOW) && (millis() - prevTime >= offInterval_0))
        {
            pulseState = HIGH;
            prevTime = millis();
        }
        digitalWrite(pin, pulseState);
    }
}