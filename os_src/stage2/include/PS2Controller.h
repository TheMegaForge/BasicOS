#pragma once
#include "SwitchHandles.h"
#include <stdbool.h>
#define KBD_DATA_PORT 0x60
#define KBD_STATUS_PORT 0x64
#define KBD_COMMAND_PORT 0x64
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
void InstallPS2(StageHandles* sh,PS2Controller* kbd);
void activeKeyboard(StageHandles* sh);