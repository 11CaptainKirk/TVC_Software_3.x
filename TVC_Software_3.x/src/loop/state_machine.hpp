#include <Arduino.h>
#include <system_state.h>
#include <loop/update_readings.hpp>
#include <loop/write_data.hpp>
#include <utility/smart_pulse_buzzer.hpp>
#include <utility/smart_pulse_LED.hpp>
#include <utility/button_read.hpp>
#include <utility/ejection.hpp>
#include <utility/error_sequence.hpp>

#ifndef STATE_MACHINE_HPP
#define STATE_MACHINE_HPP

bool hasSetDefaults = false;
float ejectionAltitudeDeltaCheck = 0;
bool hasSetEjectionAltitudeDeltaCheck = false;

bool hasSavedAltitude = false;  // Only save altitude to detect apogee once.
float savedAltitude = -1;

const int poweredAccelThreshold = 50;
const int unpoweredAccelThreshold = -5;
const int apogeeDetectAltDelta = 3;
const int ejectionAltitude = telemetry.utility.home.ejectionAltitudeMeters;

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
            telemetry.utility.home.startY = telemetry.bno055_0.processedEuler.x;
            telemetry.utility.home.startZ = telemetry.bno055_0.processedEuler.y;
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

        if (telemetry.bno055_0.rawAccel.x >= poweredAccelThreshold){ // Check to see if takeoff has occured
            systemState = POWERED_ASCENT;
        }

        break;
    case POWERED_ASCENT:
        // Takeoff ( Powered Ascent  |  a > 0  |  v > 0  )

        inFlight();
        servo(LOOP);
        failsafeEjection();

        if (telemetry.bno055_0.rawAccel.x >= poweredAccelThreshold){  // Check to see if motor has burned out
            systemState = UNPOWERED_ASCENT;
        }
        break;
    case UNPOWERED_ASCENT:
        // Motor Burnout ( Unpowered Ascent  |  a < 0  |  v > 0  )
    
        inFlight();
        servo(LOOP);
        failsafeEjection();


        if (!hasSavedAltitude){   // Save altitude
        savedAltitude = telemetry.bmp180.normalizedValues.altitude;
        hasSavedAltitude = true;
        }
        if (savedAltitude >= telemetry.bmp180.normalizedValues.altitude + apogeeDetectAltDelta){  // Check if current altitude is at least 3m less than saved altitude
            systemState = BALLISTIC_DESCENT;
        }
        break;
    case BALLISTIC_DESCENT:
        // Initially at Apogee ( Max Altitude  |  a = 0  |  v = 0  )

        inFlight();
        failsafeEjection();


        if (telemetry.bmp180.normalizedValues.altitude <= ejectionAltitude + 10){ // Add 10 because of deloyment delay
            systemState = DROGUE_CHUTE_DESCENT;
        }
        break;
    case DROGUE_CHUTE_DESCENT:
        // Ballistic Descent ( No Deployment  |  a < 0  |  v < 0  )

        inFlight();
        fireEjection();
        // ? HOW TO DETECT MAIN CHUTE DEPLOYMENT WITH JOLLY LOGIC?

        if (telemetry.bmp180.normalizedValues.altitude < ejectionAltitude-20){ // Check if rocket is 20m below ejection altitude, if so, move to main chute and initiate failover ejection.
            systemState = MAIN_CHUTE_DESCENT; // It is not actually in main chute but this is for another failover deployment opportunity.
        }

        smartPulseLED(35, 50, 50);
        smartPulseBuzzer(23, 50, 50);
        break;
    case MAIN_CHUTE_DESCENT:
        // Drogue Chute Descent ( Drogue Deployment  |  a > 0  |  v < 0  )
        failsafeEjection();
        smartPulseLED(35, 50, 50);
        smartPulseBuzzer(23, 50, 50);
        break;
    case TOUCHDOWN:
        // Main Chute Descent ( Main Deployment  |  a > 0  |  v < 0  )
        break;
    case ERROR_SD:
        // SD Card Error
        errorSequence(2, 1);
        break;
    case ERROR_IMU1:
        // SD Card Error
        errorSequence(1, 2);
        break;
    default:
        // THERE IS AN ERROR, CHECK WHAT IT IS
        Serial.println(systemState);
        // TODO: CHECK FOR ERROR
    }
}

#endif