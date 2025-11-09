#include "motor.h"
#include "stm32l4xx_hal.h"

#define MOTOR_OPEN_PIN    GPIO_PIN_1
#define MOTOR_CLOSE_PIN   GPIO_PIN_2
#define MOTOR_PORT        GPIOA

#define MOTOR_RUN_TIME_MS 5000  // stop motor automatically after 5s

TIM_HandleTypeDef htim2; // Timer for motor safety

void Motor_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    __HAL_RCC_GPIOA_CLK_ENABLE();

    GPIO_InitStruct.Pin = MOTOR_OPEN_PIN | MOTOR_CLOSE_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(MOTOR_PORT, &GPIO_InitStruct);
}

// Internal function to start safety timer
void Motor_StartTimer(void) {
    HAL_TIM_Base_Start_IT(&htim2);
}

void Motor_Open(void) {
    HAL_GPIO_WritePin(MOTOR_PORT, MOTOR_OPEN_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(MOTOR_PORT, MOTOR_CLOSE_PIN, GPIO_PIN_RESET);
    Motor_StartTimer();
}

void Motor_Close(void) {
    HAL_GPIO_WritePin(MOTOR_PORT, MOTOR_CLOSE_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(MOTOR_PORT, MOTOR_OPEN_PIN, GPIO_PIN_RESET);
    Motor_StartTimer();
}

void Motor_Stop(void) {
    HAL_GPIO_WritePin(MOTOR_PORT, MOTOR_OPEN_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_PORT, MOTOR_CLOSE_PIN, GPIO_PIN_RESET);
    HAL_TIM_Base_Stop_IT(&htim2);
}

// Timer callback to stop motor
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if (htim->Instance == TIM2) {
        Motor_Stop();
    }
}
