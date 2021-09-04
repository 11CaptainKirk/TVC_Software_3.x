#ifndef STATUS_H
#define STATUS_H

typedef enum
{
    INITIALIZING,
    GROUND_IDLE,
    COUNTDOWN,
    POWERED_ASCENT,
    UNPOWERED_ASCENT,
    APOGEE,
    BALLISTIC_DESCENT,
    DROGUE_CHUTE_DESCENT,
    MAIN_CHUTE_DESCENT,
    TOUCHDOWN,
    ERROR_IMU,
    ERROR_BARO,
    ERROR_GPS,
    ERROR_SD,
    ERROR_SERVO,
    ERROR_PID,
    ERROR_OTHER
} SystemState;

typedef enum
{
    SETUP,
    LOOP
} FunctionMode;

#endif