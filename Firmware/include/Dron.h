#pragma once
#include <GY-87.h>
#include <array>
#include "Motor.h"
#include "Control.h"

class Dron
{
private:
    static constexpr uint8_t NUMBER_OF_MOTORS = 4;
    Gy87 _gy87;
    Control _control;
    Motor _motors[NUMBER_OF_MOTORS] = {
        Motor(GPIO_NUM_8, LEDC_CHANNEL_0),
        Motor(GPIO_NUM_9, LEDC_CHANNEL_1),
        Motor(GPIO_NUM_10, LEDC_CHANNEL_2),
        Motor(GPIO_NUM_11, LEDC_CHANNEL_3),
    };
    bool _started = false;
    std::array<uint8_t, NUMBER_OF_MOTORS> CalculatePower(Control::ControlDirection direction);
    std::array<uint8_t, NUMBER_OF_MOTORS> Clamp(const std::array<float, NUMBER_OF_MOTORS> &raw);

public:
    void Init();
    void Fly();
};
