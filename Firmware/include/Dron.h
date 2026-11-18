#pragma once
#include <GY-87.h>
#include "Motor.h"

class Dron
{
private:
    Gy87 _gy87;
    Motor _motors[4] = {
        Motor(13),
        Motor(14),
        Motor(15),
        Motor(16)};

    std::array<uint8_t, 4> CalculatePower();

public:    
    void Init();
    void Fly();
};
