#include "../PCI.h"
#include "../drivers/ATAdrv.h"
#include "ATAStructs.h"
#include "ATADefs.h"
#include "IDE.h"

#pragma once
#pragma region IO_BASE
    #define PRIMARY_ATA_BUS_PORT_START 0x1F0
    #define PRIMARY_ATA_BUS_PORT_END   0x1F7

    #define SECONDARY_ATA_BUS_PORT_START 0x170
    #define SECONDARY_ATA_BUS_PORT_END 0x177
#pragma endregion IO_BASE wiki.osdev.org/ATA_PIO_Mode

#pragma region CONTROLL_BASE
    #define PRIMARY_CONTROL_BASE 0x3F6
    #define SECONDARY_CONTROL_BASE 0x376
#pragma endregion CONTROLL_BASE

#pragma region IRQ_S
    #define IRQ_PRIMARY_BUS 14
    #define IRQ_SECONDARY_BUS 15
#pragma endregion IRQ_S



void readATAController(ATAController* ata,IDEController* ide);
CMNStorageError ATAdisk(ATAController* controller,bool primary,bool read,uint32_t SecPerClu,uint32_t clusters,uint32_t lba,uint16_t* buffer);

