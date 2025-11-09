#include "app.h"
#include "motor.h"
#include "ldr.h"
#include "bluetooth.h"

void App_Init(void) {
    Motor_Init();
    LDR_Init();
    BT_Init();
}

void App_MainLoop(void) {
    while (1) {
        BT_Process();   // check bluetooth input
        LDR_Check();    // periodically check light sensor
        HAL_Delay(1000);
    }
}
