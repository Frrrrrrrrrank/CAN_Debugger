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
        Buzzer::playBlocked(0.1, 220, 500);
        HAL_ADC_Start_DMA(&hadc2, (uint32_t *) &adc_buffer, 8);
        HAL_TIM_Base_Start_IT(&htim3);
    }

}

volatile uint32_t avgV = 0;
volatile uint32_t avgA = 0;

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc) {
    int bufV = 0;
    int bufA = 0;
    for (size_t i = 0; i < 4; i++) {
        bufV += Tasks::adc_buffer[2 * i];
        bufA += Tasks::adc_buffer[2 * i + 1];
    }
    avgV = bufV / 4;
    avgA = bufA / 4;
}

extern "C" {
void SystemStart() {
    Tasks::init();
    Tasks::loop();
}
}
