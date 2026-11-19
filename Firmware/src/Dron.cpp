#include "Dron.h"
#include "Control.h"

void Dron::Init()
{
    _gy87.Initialice();
    _control.Init();

    for (Motor &i : _motors)
    {
        i.Init();
    };
}

std::array<uint8_t, 4> Dron::CalculatePower(Control::ControlDirection direction)
{
    float acceleration = _gy87.GetLinearAcceleration();
    Vector3F gyro = _gy87.GetGyro();
    float hight = _gy87.GetPresure();

    if (!_started && direction.Start)
    {
        _started = true;
    }
    else if (_started && direction.Start)
    {
        _started = false;
    }

    std::array<uint8_t, 4> power{};
    if (_started)
    {

        for (std::size_t i = 0; i < size_t(_motors); ++i)
        {
            power[i] = _motors[i].GetPower();
            power[i] += static_cast<uint8_t>(direction.Throttle);
        }

        if (direction.Pitch > 0)
        {
            power[0] -= direction.Pitch;
            power[2] -= direction.Pitch;
        }
        else if (direction.Pitch > 0)
        {
            power[1] -= direction.Pitch;
            power[3] -= direction.Pitch;
        }
        
        if (direction.Yaw < 0)
        {
            power[0] -= direction.Yaw;
            power[2] -= direction.Yaw;
        }
        else if (direction.Yaw > 0)
        {
            power[1] -= direction.Yaw;
            power[3] -= direction.Yaw;
        }

        if (direction.Roll > 0)
        {
        }
    }

    return power;
};

void Dron::Fly()
{

    Control::ControlDirection dirrection = _control.GetDirecction();
    std::array<uint8_t, 4> powerToEngines = CalculatePower(dirrection);

    for (size_t i = 0; i < powerToEngines.size(); i++)
    {
        _motors[i].Power(powerToEngines[i]);
    }
}