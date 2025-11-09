#include "bluetooth.h"
#include "ldr.h"
#include "motor.h"
#include <string.h>

UART_HandleTypeDef huart2;
char rx_data[50];

void BT_Init(void) {
    __HAL_RCC_USART2_CLK_ENABLE();

    huart2.Instance = USART2;
    huart2.Init.BaudRate = 9600;
    huart2.Init.WordLength = UART_WORDLENGTH_8B;
    huart2.Init.StopBits = UART_STOPBITS_1;
    huart2.Init.Parity = UART_PARITY_NONE;
    huart2.Init.Mode = UART_MODE_TX_RX;
    HAL_UART_Init(&huart2);
}

void BT_Process(void) {
    if (HAL_UART_Receive(&huart2, (uint8_t*)rx_data, sizeof(rx_data), 100) == HAL_OK) {
        if (strstr(rx_data, "LDR ON"))  LDR_Preference = 1;
        else if (strstr(rx_data, "LDR OFF")) LDR_Preference = 0;
        else if (strstr(rx_data, "OPEN")) Motor_Open();
        else if (strstr(rx_data, "CLOSE")) Motor_Close();
        else if (strstr(rx_data, "STOP")) Motor_Stop();
    }
}
