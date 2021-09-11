#include <Arduino.h>
#include <system_state.h>
#include <loop/update_readings.hpp>
#include <loop/write_data.hpp>
#include <utility/smart_pulse_buzzer.hpp>
#include <utility/smart_pulse_LED.hpp>
#include <utility/button_read.hpp>
#include <utility/ejection.hpp>

#ifndef STATE_MACHINE_HPP
#define STATE_MACHINE_HPP

bool hasSetDefaults = false;
float ejectionAltitudeDeltaCheck = 0;
bool hasSetEjectionAltitudeDeltaCheck = false;

void inFlight()
{
    writeData();
    readSensors();
}
void ground()
{
}
void failsafeEjection(){
    // Failsafe check for ejection (In case the state system does not correctly detect state change, this code will fire ejection charge if simple criteria are met.) 
        // TODO CHECK THIS (Maybe create new variable that is altitude-startAltitude)
        if(telemetry.bmp180.normalizedValues.altitude < telemetry.utility.home.ejectionAltitudeMeters + 30){ // Check if rocket is 30m above ejection altitude
            if (!hasSetEjectionAltitudeDeltaCheck){  // Check if altitude at 30m above ejection has been saved
            ejectionAltitudeDeltaCheck = telemetry.bmp180.normalizedValues.altitude; // If not, save it.
            hasSetEjectionAltitudeDeltaCheck = true;  // Set this to true so we don't save again.
            }
            if (ejectionAltitudeDeltaCheck - 20 > telemetry.bmp180.normalizedValues.altitude){ // Check if we have fallen more than 20 meters since initial altitude was saved.
                // ! FIRE EJECTION 
                fireEjection();
                // TODO Add ejection code
                // If so, rocket is below ejection altitude and losing significant altitude over time (in ballistic descent); fire ejection charge.
            }
        
        }
}

static void stateMachine()
{

    switch (systemState)
    {
    case INITIALIZING:
        // Initializing ( Not Ready )
        smartPulseLED(35, 100, 2000);
        smartPulseBuzzer(23, 100, 2000);
        inFlight();
        break;
    case GROUND_IDLE:
        // Ground Idle ( Ready For Flight )

        // Status Indication
        smartPulseLED(35, 1000, 1000);
        smartPulseBuzzer(23, 1000, 1000);
        // Standard Loop
        inFlight();
        // State Change checks
        if (buttonRead())
        {
            // Set defaults at current position
            telemetry.utility.home.startY = telemetry.bno055_0.processedEuler.y;
            telemetry.utility.home.startZ = telemetry.bno055_0.processedEuler.z;
            telemetry.utility.home.startAltitude = telemetry.bmp180.processedValues.altitude;

            // Change to countdown system state
            systemState = COUNTDOWN;
        }

        break;
    case COUNTDOWN:
        // Countdown ( Armed and Waiting for Liftoff )
        
        // Status Indication
        smartPulseLED(35, 200, 200);
        smartPulseBuzzer(23, 200, 200);
        // Standard Loop
        inFlight();
        servo(LOOP);
        // State Change checks
        if (!buttonRead())
        {
            systemState = GROUND_IDLE;
        }

        // Backup ejection code that runs in all states
        failsafeEjection();

        break;
    case POWERED_ASCENT:
        // Takeoff ( Powered Ascent  |  a > 0  |  v > 0  )
        break;
    case APOGEE:
        // Motor Burnout ( Unpowered Ascent  |  a < 0  |  v > 0  )
        break;
    case BALLISTIC_DESCENT:
        // Apogee ( Max Altitude  |  a = 0  |  v = 0  )
        break;
    case DROGUE_CHUTE_DESCENT:
        // Ballistic Descent ( No Deployment  |  a < 0  |  v < 0  )
        break;
    case MAIN_CHUTE_DESCENT:
        // Drogue Chute Descent ( Drogue Deployment  |  a > 0  |  v < 0  )
        break;
    case TOUCHDOWN:
        // Main Chute Descent ( Main Deployment  |  a > 0  |  v < 0  )
        break;
    case ERROR_SD:
        // SD Card Error
        smartPulseLED(35, 100, 50);
        smartPulseBuzzer(23, 100, 50);
        break;
    default:
        // THERE IS AN ERROR, CHECK WHAT IT IS
        Serial.println(systemState);
        // TODO: CHECK FOR ERROR
    }
}

#endif