#include "Dron.h"
#include "Control.h"
#include <algorithm>

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

    if (!_started)
    {
        return std::array<uint8_t, NUMBER_OF_MOTORS>();
    }

    float throttle = static_cast<float>(direction.ThrottleRT);
    float pitch = static_cast<float>(direction.Pitch);
    float roll = static_cast<float>(direction.Roll);
    float yaw = static_cast<float>(direction.Yaw);

    std::array<float, NUMBER_OF_MOTORS> raw = {
        throttle - pitch + roll - yaw, // 0: FL (CW)
        throttle - pitch - roll + yaw, // 1: FR (CCW)
        throttle + pitch + roll + yaw, // 2: RL (CCW)
        throttle + pitch - roll - yaw  // 3: RR (CW)
    };

    return Clamp(raw);
}

std::array<uint8_t, Dron::NUMBER_OF_MOTORS> Dron::Clamp(const std::array<float, NUMBER_OF_MOTORS> &raw)
{
    constexpr float MIN_PERCENT = 5.0f;
    constexpr float MAX_PERCENT = 100.0f;

    std::array<uint8_t, NUMBER_OF_MOTORS> power{};
    for (std::size_t i = 0; i < NUMBER_OF_MOTORS; ++i)
    {        
        power[i] = static_cast<uint8_t>(std::clamp(raw[i], MIN_PERCENT, MAX_PERCENT));
    }

    return power;
}

void Dron::Fly()
{

    Control::ControlDirection dirrection = _control.GetDirecction();
    std::array<uint8_t, NUMBER_OF_MOTORS> powerToEngines = CalculatePower(dirrection);

    for (size_t i = 0; i < powerToEngines.size(); i++)
    {
        _motors[i].Power(powerToEngines[i]);
    }
}