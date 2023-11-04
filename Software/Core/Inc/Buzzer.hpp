#pragma once

#include "main.h"
#include "tim.h"

namespace Buzzer {
    TIM_HandleTypeDef *BUZZER_TIMER_HANDLE = &htim8;
    uint32_t BUZZER_TIM_CHANNEL = TIM_CHANNEL_1;
    uint32_t BUZZER_TIM_COUNTER_FREQUENCY = 170000000 / 17;

    //void init();

    static uint32_t tempArr = -1;

    inline void start(float duty, uint32_t frequency) {
        tempArr = BUZZER_TIM_COUNTER_FREQUENCY / frequency;
        __HAL_TIM_SET_AUTORELOAD(BUZZER_TIMER_HANDLE, tempArr);
        __HAL_TIM_SET_COMPARE(BUZZER_TIMER_HANDLE, BUZZER_TIM_CHANNEL, tempArr * duty);
        HAL_TIM_PWM_Start(BUZZER_TIMER_HANDLE, BUZZER_TIM_CHANNEL);
    }

    inline void stop() {
        HAL_TIM_PWM_Stop(BUZZER_TIMER_HANDLE, BUZZER_TIM_CHANNEL);
    }

    inline void playBlocked(float duty, uint32_t frequency, uint32_t durationMs) {
        start(duty, frequency);
        HAL_Delay(durationMs);
        stop();

    }

    //void sequence();

}