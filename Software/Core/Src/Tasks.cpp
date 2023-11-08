#include "main.h"
#include "adc.h"
#include "dma.h"
#include "stm32g4xx_hal.h"
#include "stm32g4xx_hal_adc.h"

#include "Buzzer.hpp"
#include "Sense.hpp"


namespace Tasks {
    static void loop() {
        for (;;) {
            //dummy
        }
    }

    void init() {
        Buzzer::playBlocked(0.1, 220, 500);
        HAL_ADC_Start_DMA(&hadc2, (uint32_t *) &Sense::adc_buffer, 8);
        HAL_TIM_Base_Start_IT(&htim3);
    }
}


extern "C" {
void SystemStart() {
    Tasks::init();
    Tasks::loop();
}
}
