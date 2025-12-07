#include "uartcmds.h"

static UART_HandleTypeDef *cmd_huart;
static uint8_t rxByte;              // Buffer for 1 character
static volatile char receivedCmd = 0; // Command storage for App

void UART_Init(UART_HandleTypeDef *huart) {
    cmd_huart = huart;
}

// 1. Call this ONCE in App_Initialize
void UART_StartRX(void) {
    // Start listening for 1 byte using Interrupts
    HAL_UART_Receive_IT(cmd_huart, &rxByte, 1);
}

// 2. App calls this to retrieve data
char UART_GetCommand(void) {
    char c = receivedCmd;
    receivedCmd = 0; // Clear it so we don't trigger twice
    return c;
}

// 3. The Interrupt Callback (Runs automatically when data arrives)
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    // Verify this interrupt belongs to our UART
    if (huart->Instance == cmd_huart->Instance) {

        // Save the received character
        receivedCmd = (char)rxByte;

        // Restart the Interrupt Listener immediately
        HAL_UART_Receive_IT(cmd_huart, &rxByte, 1);
    }
}

// --- Printing Functions ---

void UART_TransmitString(char a_string[], int newline) {
    HAL_UART_Transmit(cmd_huart, (uint8_t*)a_string, strlen(a_string), 100);
    if (newline) {
        HAL_UART_Transmit(cmd_huart, (uint8_t*)"\r\n", 2, 100);
    }
}

void ShowCommands(void) {
    UART_TransmitString("\r\n--- MENU ---", 1);
    UART_TransmitString("O: Open | X: Close", 1);
    UART_TransmitString("S: Status", 1);
    UART_TransmitString("T: Auto ON | t: Auto OFF", 1);
}

void UART_PrintStatus(const char *action, int position, int maxSteps, float voltage) {
    char buffer[128];
    sprintf(buffer, "\r\nAction: %s | Pos: %d/%d | V: %.2f",
            action, position, maxSteps, voltage);
    UART_TransmitString(buffer, 1);
}
