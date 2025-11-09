#include "ldr.h"
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
}
