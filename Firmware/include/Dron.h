#pragma once
#include <GY-87.h>
#include <array>
#include "Motor.h"


class Dron
{
private:
    Gy87 _gy87;
    Motor _motors[4] = {
    Motor(GPIO_NUM_13),
    Motor(GPIO_NUM_14),
    Motor(GPIO_NUM_15),
    Motor(GPIO_NUM_16),
};

    std::array<uint8_t, 4> CalculatePower();

public:    
    void Init();
    void Fly();
};
