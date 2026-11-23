#pragma once
#include "driver/gpio.h"
#include "driver/ledc.h"
#include <cstdint>

class Motor
{
private:    
    static constexpr uint32_t PWM_FREQ_HZ = 20000;
    static constexpr ledc_mode_t PWM_MODE = LEDC_LOW_SPEED_MODE;
    static constexpr ledc_timer_t PWM_TIMER = LEDC_TIMER_0;
    static constexpr ledc_timer_bit_t PWM_RESOLUTION = LEDC_TIMER_8_BIT;

    static inline bool _timerInitialized = false;

    uint8_t _pwrPercentage = 0;
    uint8_t _pwr = 0;
    gpio_num_t _pin = GPIO_NUM_NC;
    ledc_channel_t _channel = LEDC_CHANNEL_0;

public:
    uint8_t GetPower() const;
    Motor(gpio_num_t pin, ledc_channel_t channel);
    void Init();
    void Power(uint8_t pwrPercentage);
};


