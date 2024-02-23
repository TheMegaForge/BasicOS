#pragma once
#include <stdbool.h>
#include "LBA.h"
#include "IDE.h"
/*
    validation flags
    =>
        00100000

        00100001 => master/slave-0
        00100010
        00100011

        00100101
        00100110
        00100111 => master/slave-1


*/
typedef enum{
    ATA_VALIDATION_NOTHING    = 0b00100000,
    ATA_VALIDATION_MASTER0    = 0b00000001,
    ATA_VALIDATION_SLAVE0     = 0b00000010,
    ATA_VALIDATION_MASTER1    = 0b00000101,
    ATA_VALIDATION_SLAVE1     = 0b00000110,
    
    ATA_VALIDATION_ALL_0      = 0b00000011,
    ATA_VALIDATION_ALL_1      = 0b00000111
}_CATAValidation;
typedef struct{
    bool isHardDrive;
    bool supports48LBA;
    uint8_t supportedUDMA_Models;
    uint8_t activeUDMA_Model;
    bool detected80ConductorCable;
    uint32_t maxLBA28;
    LBA48_32BitMode MaxLba48;
}__attribute__((packed)) ATAInformation;
typedef struct{
    ATAInformation  info[2];
    IDEChannel      master0;
    IDEChannel      slave0;
    _CATAValidation validation;
}__attribute__((packed)) ATAController;