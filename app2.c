#include "app.h"
#include "motor.h"
#include "ldr.h"
#include "uartcmds.h"
#include <stdbool.h>
#include <stdio.h>

static bool ldrPrecedence = false;
static float currentVoltage = 0.0f;

static void PerformOpen(void) {
    int currentPos = Motor_GetPosition();
    if (currentPos >= MAX_STEPS) {
        UART_TransmitString("ERROR: Curtain already OPEN.", 1);
        return;
    }
    UART_PrintStatus("Opening...", currentPos, MAX_STEPS, currentVoltage);

    // Move Motor
    Motor_Step(MAX_STEPS - currentPos);

    UART_TransmitString("Curtain Fully Open", 1);
}

static void PerformClose(void) {
    int currentPos = Motor_GetPosition();
    if (currentPos <= 0) {
        UART_TransmitString("ERROR: Curtain already CLOSED.", 1);
        return;
    }
    UART_PrintStatus("Closing...", currentPos, MAX_STEPS, currentVoltage);

    // Move Motor
    Motor_Step(-currentPos);

    UART_TransmitString("Curtain Fully Closed", 1);
}

static void CheckLDR(void) {
    // Read the Voltage
    currentVoltage = LDR_ReadVoltage();

    // Continuous Display (Only if Auto Mode is ON)
    if (ldrPrecedence) {
        char buf[64];
        // Print voltage clearly
        sprintf(buf, "AUTO MODE | LDR Voltage: %.2f V", currentVoltage);
        UART_TransmitString(buf, 1);

        // Check Triggers
        if (currentVoltage > OPEN_THRESHOLD && Motor_GetPosition() < MAX_STEPS) {
            UART_TransmitString(">>> Light Trigger: OPENING...", 1);
            PerformOpen();
        }
        else if (currentVoltage < CLOSE_THRESHOLD && Motor_GetPosition() > 0) {
            UART_TransmitString(">>> Dark Trigger: CLOSING...", 1);
            PerformClose();
        }
    }
}

void App_Initialize(UART_HandleTypeDef *huart, ADC_HandleTypeDef *hadc) {
    UART_Init(huart);
    LDR_Init(hadc);
    Motor_Init();

    // Start the Interrupt Listener
    UART_StartRX();

    UART_TransmitString("\r\nSYSTEM READY.", 1);
    ShowCommands();
}

void App_MainLoop(void) {
    static uint32_t lastLDRCheck = 0;

    // Check for UART Commands
    char cmd = UART_GetCommand();

    if (cmd != 0) {
        char echoMsg[32];
        sprintf(echoMsg, "Command: %c", cmd);
        UART_TransmitString(echoMsg, 1);

        switch (cmd) {
            case 'O': case 'o':
                if (!ldrPrecedence) PerformOpen();
                else UART_TransmitString("REJECTED: Auto Mode ON", 1);
                break;
            case 'X': case 'x':
                if (!ldrPrecedence) PerformClose();
                else UART_TransmitString("REJECTED: Auto Mode ON", 1);
                break;
            case 'S': case 's':
                UART_PrintStatus("Status", Motor_GetPosition(), MAX_STEPS, currentVoltage);
                break;
            case 'T':
                ldrPrecedence = true;
                UART_TransmitString("Auto Mode: ON (Monitoring Voltage...)", 1);
                break;
            case 't':
                ldrPrecedence = false;
                UART_TransmitString("Auto Mode: OFF", 1);
                break;
            case 'H': case 'h':
                ShowCommands();
                break;
        }
    }

    // Check LDR continuously (every 500ms)
    if (HAL_GetTick() - lastLDRCheck > 500) {
        CheckLDR();
        lastLDRCheck = HAL_GetTick();
    }
}
