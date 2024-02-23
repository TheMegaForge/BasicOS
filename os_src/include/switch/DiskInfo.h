#pragma once
#include "../storage/IDE.h"
#include "../storage/ATA.h"
#include <stdint.h>
typedef struct{
    IDEController* cntrl;
    ATAController* dskCntrl;
    StorageCommon* cmnStorage;
}DiskInfo;

typedef struct{
    uint32_t t_dsk1GIBs;
    uint32_t t_dsk1MIBs;
    uint32_t t_dsk1KIBs;
}StorageInfo;