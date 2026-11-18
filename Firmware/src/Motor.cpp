#include "Motor.h"
#include "driver/gpio.h"

Motor::Motor(gpio_num_t pin)
{
    _pin = pin;
}

void Motor::Init()
{
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << _pin),  // Select the GPIO to configure
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
        
      //  analogWrite(_pin, _pwr);
    }
    else
    {
        _pwr = pwrPorcentage * 2.55;
      //  analogWrite(_pin, _pwr);
    }
}