#ifndef STATUS_H
#define STATUS_H

typedef enum
{
    INITIALIZING,
    READY,
    GROUND_IDLE,
    COUNTDOWN,
    POWERED_ASCENT,
    UNPOWERED_ASCENT,
    APOGEE,
    BALLISTIC_DESCENT,
    DROGUE_CHUTE_DESCENT,
    MAIN_CHUTE_DESCENT,
    TOUCHDOWN,
    ERROR_IMU0,
    ERROR_IMU1,
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