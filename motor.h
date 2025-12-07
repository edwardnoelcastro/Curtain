/*
 * motor.h
 *
 *  Created on: Nov 30, 2025
 *      Author: jeremiahtollossa
 */

#ifndef MOTOR_H
#define MOTOR_H

#include "main.h" // Includes STM32 HAL

// Step Configuration
#define MAX_STEPS 1250
#define MOTOR_SPEED_DELAY 3 // ~3ms delay between steps

// Motor State Definition
typedef struct {
    int currentPosition;
    int targetPosition;
} Motor_State_t;

// Function Prototypes
void Motor_Init(void);
void Motor_Step(int steps);
void Motor_Off(void);
int Motor_GetPosition(void);
void Motor_SetPosition(int pos);

#endif









//Old motor.h
/*// motor.h
#ifndef MOTOR_H
#define MOTOR_H

#include "stm32l4xx_hal.h"

void Motor_Init(void);
void Motor_Open(void);
void Motor_Close(void);
void Motor_Stop(void);

#endif
*/
