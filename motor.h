// motor.h
#ifndef MOTOR_H
#define MOTOR_H

#include "stm32l4xx_hal.h"

void Motor_Init(void);
void Motor_Open(void);
void Motor_Close(void);
void Motor_Stop(void);

#endif
