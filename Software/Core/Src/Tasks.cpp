#include "main.h"
#include "Buzzer.hpp"
#include "adc.h"
#include "dma.h"
#include "stm32g4xx_hal.h"

#include "stm32g4xx_hal_adc.h"


namespace Tasks {
    static void loop() {
        for (;;) {
            //dummy
        }
    }

    volatile uint16_t adc_buffer[8] = {0};


    void init() {
        Buzzer::playBlocked(0.1, 220, 1000);
        HAL_ADC_Start_DMA(&hadc2, (uint32_t *) &adc_buffer, 8);
        HAL_TIM_Base_Start_IT(&htim3);
    }

}

volatile uint32_t avg = 0;

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc) {
    int buf = 0;
    for (unsigned short i: Tasks::adc_buffer) {
        buf += i;
    }
    avg = buf / 8;
}

extern "C" {
void SystemStart() {
    Tasks::init();
    Tasks::loop();
}
}
