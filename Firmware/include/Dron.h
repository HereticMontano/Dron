#pragma once
#include <GY-87.h>
#include <array>
#include "Motor.h"
#include "Control.h"

class Dron
{
private:
    Gy87 _gy87;
    Control _control;
    Motor _motors[4] = {
        Motor(GPIO_NUM_8),
        Motor(GPIO_NUM_9),
        Motor(GPIO_NUM_10),
        Motor(GPIO_NUM_11),
    };
    bool _started = false;
    std::array<uint8_t, 4> CalculatePower(Control::ControlDirection direction);

public:
    void Init();
    void Fly();
};
