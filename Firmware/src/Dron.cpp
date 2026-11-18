#include "Dron.h"

void Dron::Init()
{
    _gy87.Initialice();

    for (Motor &i : _motors)
    {
        i.Init();
    };
}

std::array<uint8_t, 4> Dron::CalculatePower()
{
    Vector3F acceleration = _gy87.GetAcceleration();
    Vector3 gyro = _gy87.GetGyro();
    float hight = _gy87.GetPresure();

    if (acceleration.X == 0 && acceleration.Y == 0 && acceleration.Z == 0 &&
        gyro.X == 0 && gyro.Y == 0 && gyro.Z == 0)
    {
        return {5, 5, 5, 5};
    }

    return {0, 0, 0, 0};
};

void Dron::Fly()
{
    std::array<uint8_t, 4> powerToEngines = CalculatePower();

    for (size_t i = 0; i < powerToEngines.size(); i++)
    {
        _motors[i].Power(powerToEngines[i]);
    }
}