#pragma once
#include "SwitchHandles.h"
#include "PS2Controller.h"
#include <stdbool.h>
#include "hw/KBDDriver.h"
#define KBD_SCAN_ERROR 0x4f
#define KBD_DRV_SUB_ID 0xDB
typedef struct{
    uint8_t scanSet;
    bool okay;
}Keyboard;

void prepareKeyboard(StageHandles* sh,PS2Device* ps2,Keyboard* kbd);
void createDriver(KBDDriver* drv,Keyboard* kbd,StageHandles* sh);