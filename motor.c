#include "motor.h"
#include <stdlib.h>

#define IN1_PORT GPIOA
#define IN1_PIN  GPIO_PIN_9 // D8

#define IN2_PORT GPIOC
#define IN2_PIN  GPIO_PIN_7 // D9

#define IN3_PORT GPIOB
#define IN3_PIN  GPIO_PIN_6 // D10

#define IN4_PORT GPIOA
#define IN4_PIN  GPIO_PIN_7 // D11

// Full Step Sequence (Wave Drive)
const uint8_t stepSequence[4][4] = {
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1}
};

static Motor_State_t motorState = {0, 0};

void Motor_Init(void) {
    Motor_Off();
    motorState.currentPosition = 0; // Assume closed on startup
}

void Motor_Off(void) {
    HAL_GPIO_WritePin(IN1_PORT, IN1_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(IN2_PORT, IN2_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(IN3_PORT, IN3_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(IN4_PORT, IN4_PIN, GPIO_PIN_RESET);
}

void Motor_Step(int steps) {
    int direction = (steps > 0) ? 1 : -1;
    int stepsLeft = abs(steps);
    static int stepIndex = 0;

    while (stepsLeft > 0) {
        // 1. Write the GPIOs based on current step index
        HAL_GPIO_WritePin(IN1_PORT, IN1_PIN, (stepSequence[stepIndex][0]) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        HAL_GPIO_WritePin(IN3_PORT, IN3_PIN, (stepSequence[stepIndex][1]) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        HAL_GPIO_WritePin(IN2_PORT, IN2_PIN, (stepSequence[stepIndex][2]) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        HAL_GPIO_WritePin(IN4_PORT, IN4_PIN, (stepSequence[stepIndex][3]) ? GPIO_PIN_SET : GPIO_PIN_RESET);

        // 2. Delay for Speed Control
        HAL_Delay(MOTOR_SPEED_DELAY);

        // 3. Update Index
        if (direction == 1) {
            stepIndex++;
            if (stepIndex > 3) stepIndex = 0;
            motorState.currentPosition++;
        } else {
            stepIndex--;
            if (stepIndex < 0) stepIndex = 3;
            motorState.currentPosition--;
        }

        stepsLeft--;
    }

    // Safety: Turn off coils after move
    Motor_Off();
}

int Motor_GetPosition(void) {
    return motorState.currentPosition;
}

void Motor_SetPosition(int pos) {
    motorState.currentPosition = pos;
}











//Old Motor.c
/*#include "motor.h"
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
}*/

