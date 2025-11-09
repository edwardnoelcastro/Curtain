// bluetooth.h
#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include "stm32l4xx_hal.h"

void BT_Init(void);
void BT_Process(void);
extern UART_HandleTypeDef huart2;

#endif
