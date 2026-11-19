#include "Motor.h"

Motor::Motor(gpio_num_t pin)
{
    _pin = pin;
}

uint8_t Motor::GetPower()
{
    return _pwr / SCALE_POWER;
}

void Motor::Init()
{
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << _pin),        // Select the GPIO to configure
        .mode = GPIO_MODE_OUTPUT,              // Set as output mode
        .pull_up_en = GPIO_PULLUP_DISABLE,     // Disable pull-up
        .pull_down_en = GPIO_PULLDOWN_DISABLE, // Disable pull-down
        .intr_type = GPIO_INTR_DISABLE         // Disable interrupt
    };
    gpio_config(&io_conf);
}

void Motor::Power(uint8_t pwrPorcentage)
{
    if (pwrPorcentage >= 100)
    {
        _pwr = 255;
        gpio_set_level(_pin, _pwr);
    }
    else
    {
        _pwr = pwrPorcentage * SCALE_POWER;
        gpio_set_level(_pin, _pwr);
    }
}