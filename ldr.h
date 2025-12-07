/*
 * ldr.h
 *
 *  Created on: Nov 30, 2025
 *      Author: jeremiahtollossa
 */

#ifndef LDR_H
#define LDR_H

#include "main.h"

// Thresholds in Volts (3.3V Logic)
#define OPEN_THRESHOLD  0.9f
#define CLOSE_THRESHOLD 0.5f

void LDR_Init(ADC_HandleTypeDef *hadc);
float LDR_ReadVoltage(void);

#endif







//Old ldr.h
/*
// ldr.h
#ifndef LDR_H
#define LDR_H

#include "stm32l4xx_hal.h"

void LDR_Init(void);
void LDR_Check(void); // periodically called in main loop

extern uint8_t LDR_Preference; // 1 = ON, 0 = OFF

#endif
*/

