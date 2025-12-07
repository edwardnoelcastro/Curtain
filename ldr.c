
/*
 * ldr.c
 *
 *  Created on: Nov 30, 2025
 *      Author: jeremiahtollossa
 */

#include "ldr.h"

static ADC_HandleTypeDef *ldr_hadc;

void LDR_Init(ADC_HandleTypeDef *hadc) {
    ldr_hadc = hadc;
}

float LDR_ReadVoltage(void) {
    // 1. Start ADC Conversion
    HAL_ADC_Start(ldr_hadc);

    // 2. Wait for conversion to finish
    if (HAL_ADC_PollForConversion(ldr_hadc, 10) == HAL_OK) {
        uint32_t rawValue = HAL_ADC_GetValue(ldr_hadc);

        // 3. Convert to Voltage (12-bit ADC = 4095 max, Vref = 3.3V)
        float voltage = (float)rawValue * (3.3f / 4095.0f);
        return voltage;
    }

    return -1.0f; // Error
}


//Old LDR.c
/*#include "ldr.h"
#include "motor.h"

ADC_HandleTypeDef hadc1;
uint8_t LDR_Preference = 1; // TRUE by default

#define LDR_SAMPLES 10

void LDR_Init(void) {
    __HAL_RCC_ADC_CLK_ENABLE();
    hadc1.Instance = ADC1;
    hadc1.Init.Resolution = ADC_RESOLUTION_12B;
    HAL_ADC_Init(&hadc1);
}

// Called by TIM interrupt
void LDR_Check(void) {
    if (!LDR_Preference) return;

    uint32_t sum = 0;
    for (int i = 0; i < LDR_SAMPLES; i++) {
        HAL_ADC_Start(&hadc1);
        HAL_ADC_PollForConversion(&hadc1, 10);
        sum += HAL_ADC_GetValue(&hadc1);
        HAL_ADC_Stop(&hadc1);
    }
    uint32_t avg = sum / LDR_SAMPLES;

    if (avg > 3000) Motor_Close();
    else if (avg < 1500) Motor_Open();
}*/

