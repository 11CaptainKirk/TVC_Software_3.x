

struct SensorData
{
    IMU IMU0;
};

class IMU
{
    struct Axes
    {
        float x;
        float y;
        float z;
        float w;
    };

public:
    Axes rawEuler0; // IMU 0
    Axes rawEuler1; // IMU 1
    Axes rawEuler2;
};