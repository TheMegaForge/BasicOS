#pragma once
#include "common/Storage.h"
#include "../Driver.h"
#include "../storage/ATAStructs.h"
typedef struct _ATAAccess{
    ATAController* controller;
    uint8_t primary;
}ATAAccess;
typedef StorageCommon ATAStorage;
#define ATA_ID 0x1
void ATAregister(ATAStorage* out);