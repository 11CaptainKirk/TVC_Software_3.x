#include <Arduino.h>
#include <system_state.h>
#include <loop/update_readings.hpp>
#include <loop/write_data.hpp>
#include <utility/smart_pulse_buzzer.hpp>
#include <utility/smart_pulse_LED.hpp>
#include <utility/button_read.hpp>

#ifndef STATE_MACHINE_HPP
#define STATE_MACHINE_HPP

void inFlight()
{
    writeData();
    readSensors();
}
void ground()
{
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

        smartPulseLED(35, 1000, 1000);
        smartPulseBuzzer(23, 1000, 1000);
        inFlight();
        if (buttonRead())
        {
            systemState = COUNTDOWN;
        }

        break;
    case COUNTDOWN:
        // Countdown ( Armed and Waiting for Liftoff )
        smartPulseLED(35, 200, 200);
        smartPulseBuzzer(23, 200, 200);
        inFlight();
        if (!buttonRead())
        {
            systemState = GROUND_IDLE;
        }
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
    default:
        // THERE IS AN ERROR, CHECK WHAT IT IS
        Serial.println(systemState);
        // TODO: CHECK FOR ERROR
    }
}

#endif