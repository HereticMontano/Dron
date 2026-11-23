#include "Motor.h"

Motor::Motor(gpio_num_t pin, ledc_channel_t channel)    
{
    _pin = pin;
    _channel = channel;
}

uint8_t Motor::GetPower() const
{
    return _pwrPercentage;
}

void Motor::Init()
{
    if (!_timerInitialized)
    {
        ledc_timer_config_t timer_conf = {};
        timer_conf.speed_mode = PWM_MODE;
        timer_conf.duty_resolution = PWM_RESOLUTION;
        timer_conf.timer_num = PWM_TIMER;
        timer_conf.freq_hz = PWM_FREQ_HZ;
        timer_conf.clk_cfg = LEDC_AUTO_CLK;
        ledc_timer_config(&timer_conf);

        _timerInitialized = true;
    }

    ledc_channel_config_t channel_conf = {};
    channel_conf.gpio_num = _pin;
    channel_conf.speed_mode = PWM_MODE;
    channel_conf.channel = _channel;
    channel_conf.timer_sel = PWM_TIMER;
    channel_conf.duty = 0;
    channel_conf.hpoint = 0;

    ledc_channel_config(&channel_conf);
}

void Motor::Power(uint8_t pwrPercentage)
{
    if (pwrPercentage >= 100)
    {
        _pwrPercentage = 100;
        _pwr = 255;
    }
    else
    {
        _pwrPercentage = pwrPercentage;

        static constexpr float SCALE_POWER = 2.55f;
        _pwr = static_cast<uint8_t>(pwrPercentage * SCALE_POWER);
    }

    ledc_set_duty(PWM_MODE, _channel, _pwr);
    ledc_update_duty(PWM_MODE, _channel);
}