/*
 * uartcmds.h
 *
 *  Created on: Nov 30, 2025
 *      Author: jeremiahtollossa
 */
#ifndef UARTCMDS_H
#define UARTCMDS_H

#include "main.h"
#include <string.h>
#include <stdio.h>

// Initialization
void UART_Init(UART_HandleTypeDef *huart);

// Interrupt Control
void UART_StartRX(void);           // Starts the Interrupt Listener
char UART_GetCommand(void);        // Returns the last received command (or 0)

// Printing Helpers
void UART_TransmitString(char a_string[], int newline);
void ShowCommands(void);
void UART_PrintStatus(const char *action, int position, int maxSteps, float voltage);

#endif
