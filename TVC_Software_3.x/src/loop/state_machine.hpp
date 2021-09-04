#include <Arduino.h>
#include <system_state.h>

SystemState systemState;

static SystemState stateMachine(SystemState systemState)
{
    switch (systemState)
    {
    case INITIALIZING:
        // Initializing ( Not Ready )
        break;
    case GROUND_IDLE:
        // Ground Idle ( Ready For Flight )
        break;
    case COUNTDOWN:
        // Countdown ( Armed and Waiting for Liftoff )
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
    case ERROR_IMU:
        // Main Chute Descent ( Main Deployment  |  a > 0  |  v < 0  )
        break;
    default:
        // code block
        Serial.println("TEST");
    }
    return systemState;
}

void inFlight()
{
}
void ground()
{
}