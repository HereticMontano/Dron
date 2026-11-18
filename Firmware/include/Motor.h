#pragma once
#include <cstdint>

class Motor
{
private:
    uint8_t _pwr = 0;
    uint8_t _pin = 0;

    /* data */
public:
    Motor(uint8_t pin);
    void Init();
    void Power(uint8_t pwr);

};


