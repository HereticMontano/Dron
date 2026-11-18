#include "Motor.h"
#include <Arduino.h>

Motor::Motor(uint8_t pin)
{
    _pin = pin;
}

void Motor::Init()
{
    pinMode(_pin, OUTPUT);
    Power(0);
}

void Motor::Power(uint8_t pwrPorcentage)
{
    if (pwrPorcentage >= 100)
    {
        _pwr = 255;
        analogWrite(_pin, _pwr);
        
    }
    else
    {
        _pwr =  pwrPorcentage * 2.55;
        analogWrite(_pin, _pwr);
    }    
}