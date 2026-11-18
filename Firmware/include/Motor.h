#pragma once
#include <cstdint>
#include "driver/gpio.h"

class Motor
{
private:
    uint8_t _pwr = 0;
    gpio_num_t _pin = GPIO_NUM_NC;
    
public:
    Motor(gpio_num_t pin);
    void Init();
    void Power(uint8_t pwr);

};


