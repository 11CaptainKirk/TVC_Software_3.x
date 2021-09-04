#include <Arduino.h>

void stateMachine(int systemState)
{
    switch (systemState)
    {
    case 0:
        // Initializing ( Not Ready )
        break;
    case 1:
        // Ground Idle ( Ready For Flight )
        break;
    case 2:
        // System Armed ( Waiting for Liftoff )
        break;
    case 3:
        // Takeoff ( Powered Ascent  |  a > 0  |  v > 0  )
        break;
    case 4:
        // Motor Burnout ( Unpowered Ascent  |  a < 0  |  v > 0  )
        break;
    case 5:
        // Apogee ( Max Altitude  |  a = 0  |  v = 0  )
        break;
    case 6:
        // Ballistic Descent ( No Deployment  |  a < 0  |  v < 0  )
        break;
    case 7:
        // Drogue Chute Descent ( Drogue Deployment  |  a > 0  |  v < 0  )
        break;
    case 8:
        // Main Chute Descent ( Main Deployment  |  a > 0  |  v < 0  )
        break;
    case 9:
        // Main Chute Descent ( Main Deployment  |  a > 0  |  v < 0  )
        break;
    default:
        // code block

        Serial.println("TEST");
    }
}