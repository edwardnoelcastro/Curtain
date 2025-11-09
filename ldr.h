// ldr.h
#ifndef LDR_H
#define LDR_H

#include "stm32l4xx_hal.h"

void LDR_Init(void);
void LDR_Check(void); // periodically called in main loop

extern uint8_t LDR_Preference; // 1 = ON, 0 = OFF

#endif
