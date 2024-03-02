#pragma once
#include "SwitchHandles.h"
#include <stdbool.h>
#define KBD_DATA_PORT 0x60
#define KBD_STATUS_PORT 0x64
#define KBD_COMMAND_PORT 0x64
#define PS2_DRV_ID       0x1F//looks like IF(inter-face)
typedef enum{
    KPR_PASSED                = 0,
    KPR_CLOCK_LINE_STUCK_LOW  = 1,
    KPR_CLOCK_LINE_STUCK_HIGH = 2,
    KPR_DATA_LINE_STUCK_LOW   = 3,
    KPR_DATA_LINE_STUCK_HIGH  = 4,
    KPR_NO_RESULT             = 0xF0
}PS2POST;
typedef enum {
    PSC_ACC = 0xFA,
    PSC_FAIL = 0xFC,
    PSC_SUC = 0xAA,
    PSC_BOTH = (0xAA|0xFA)-11,
    PSC_NO_DEVICE = 0xF0
}PS2COST;
typedef struct {
    bool isDualChannled;
    bool okay;
    PS2POST probeRes[2];
    PS2COST CRes[2];
}PS2Controller;
typedef enum{
    PSD_PS2_MOUSE    = 0,
    PSD_MOUSE_SCROLL = 0x3,
    PSD_5_BTN_MOUSE  = 0x4,
    PSD_BASE         = 0xAB,
    PSD_MF_KBD       = 0x83,
    PSD_MF_KBD_2     = 0xC1,
    PSD_SHORT_DEV    = 0x84,
    PSD_NCD_KBD      = 0x85,
    PSD_122_KBD      = 0x86,
    PSD_JPN_G_KBD    = 0x90,
    PSD_JPN_P_KBD    = 0x90,
    PSD_JPN_A_KBD    = 0x92,
    PSD_NCD_SUN_KBD  = 0xA1,
    PSD_ERROR        = 0xFFAA,
    PSD_NO_DEV       = 0xFA1D,
}PS2Device;
uint8_t readIO_(StageHandles* sh,uint16_t port);
void writeFirstPort(StageHandles* sh,uint8_t data);
void writeSecondPort(StageHandles* sh,uint8_t data);
void InstallPS2(StageHandles* sh,PS2Controller* kbd);
void detectPS2Devices(StageHandles* sh,PS2Controller* cntrl,PS2Device* devices);
void unlockDevices(StageHandles* sh);