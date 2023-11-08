#include "Sense.hpp"
#include "main.h"
#include "adc.h"

volatile uint32_t avgV = 0;
volatile uint32_t avgA = 0;
volatile uint32_t avgO = 0;
volatile float ratioA = 0;

volatile uint16_t Sense::adc_buffer[12] = {0};

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc) {
    int bufV = 0;
    int bufA = 0;
    int bufO = 0;
    for (size_t i = 0; i < 4; i++) {
        bufV += Sense::adc_buffer[3 * i];
        bufA += Sense::adc_buffer[3 * i + 1];
        bufO += Sense::adc_buffer[3 * i + 2];
    }
    avgV = bufV / 4;
    avgA = bufA / 4;
    avgO = bufO / 4;
    ratioA = static_cast< float > (avgA) / static_cast< float > (avgO);
}
