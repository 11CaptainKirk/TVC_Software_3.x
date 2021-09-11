#include <Arduino.h>
#include <telemetry.h>

int timeOfLastRun = 0;

void fireEjection(){
    
    if ( millis() - timeOfLastRun > 175 ){  // Check to see if 200ms have elapsed to fire again. ( 200ms between each charge firing, 175 between fire cycles)
    digitalWrite(telemetry.utility.gpio.pyro1, HIGH);
    telemetry.utility.home.pyro1Status = true;
        if ( millis() - timeOfLastRun > 200 ){  // Check to see if 25 ms have elapsed to turn off pyro 1 and turn on pyro 2.
            digitalWrite(telemetry.utility.gpio.pyro1, LOW);
            telemetry.utility.home.pyro1Status = false;
            digitalWrite(telemetry.utility.gpio.pyro2, HIGH);
            telemetry.utility.home.pyro2Status = true;
            if ( millis() - timeOfLastRun > 225 ){   // Check to see if 25 ms have elapsed to turn off pyro 2.
                digitalWrite(telemetry.utility.gpio.pyro2, LOW);
                telemetry.utility.home.pyro2Status = false;
                timeOfLastRun = millis();       // Set time of last run to indicate that this is the time the last run finished
            }
        }
    }
}