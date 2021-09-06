#include <cmath>
#include <telemetry.h>
#include <Arduino.h>

class QuatCorrect
{
public:
    struct Quat4d
    {
        double x, y, z, w;
    };

private:
    struct EulerAngles
    {
        double x, y, z;
    };

    Quat4d correctQuaternion(Quat4d q1, Quat4d q2)
    {
        Quat4d cQuat;
        cQuat.x = q1.x * q2.w + q1.y * q2.z - q1.z * q2.y + q1.w * q2.x;
        cQuat.y = -q1.x * q2.z + q1.y * q2.w + q1.z * q2.x + q1.w * q2.y;
        cQuat.z = q1.x * q2.y - q1.y * q2.x + q1.z * q2.w + q1.w * q2.z;
        cQuat.w = -q1.x * q2.x - q1.y * q2.y - q1.z * q2.z + q1.w * q2.w;
        return cQuat;
    }

    EulerAngles toEulerAngles(Quat4d q)
    {
        EulerAngles angles;

        // roll (x-axis rotation)
        double sinr_cosp = 2 * (q.w * q.x + q.y * q.z);
        double cosr_cosp = 1 - 2 * (q.x * q.x + q.y * q.y);
        angles.x = std::atan2(sinr_cosp, cosr_cosp);

        // pitch (y-axis rotation)
        double sinp = 2 * (q.w * q.y - q.z * q.x);
        if (std::abs(sinp) >= 1)
            angles.y = std::copysign(3.14159 / 2, sinp); // use 90 degrees if out of range
        else
            angles.y = std::asin(sinp);

        // yaw (z-axis rotation)
        double siny_cosp = 2 * (q.w * q.z + q.x * q.y);
        double cosy_cosp = 1 - 2 * (q.y * q.y + q.z * q.z);
        angles.z = std::atan2(siny_cosp, cosy_cosp);

        return angles;
    }

public:
    void correctEuler(Quat4d q1)
    {
        Quat4d q2;
        q2.x = 0;
        q2.y = std::sin((std::sqrt(2)) / 2);
        q2.z = 0;
        q2.w = std::cos((std::sqrt(2)) / 2);
        //
        EulerAngles cEuler;
        cEuler = toEulerAngles(correctQuaternion(q1, q2));
        telemetry.bno055_0.processedEuler.x = cEuler.x*(180/3.14159);
        telemetry.bno055_0.processedEuler.y = cEuler.y*(180/3.14159);
        telemetry.bno055_0.processedEuler.z = cEuler.z*(180/3.14159);
    }
};
