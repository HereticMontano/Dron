#pragma once
#include "driver/gpio.h"

class Motor
{
private:
    static constexpr float SCALE_POWER = 2.22f;
    uint8_t _pwr = 0;
    gpio_num_t _pin = GPIO_NUM_NC;    
    
public:
    uint8_t GetPower();
    Motor(gpio_num_t pin);
    void Init();
    void Power(uint8_t pwr);

};


