#pragma once
#include <stdbool.h>
#include <stdint.h>
#include "../PCI.h"
//compatibility mode (ports 0x170-0x177, 0x376, IRQ14-15).
/*
    nativeModeMask
    ->
        10000001 => channel2 is native
        10000010 => channel1 is native
        10000011 => both are native
        10000000 => verification bit
*/
typedef enum {
    IDE_CHANNEL_NO_NATIVE = 0b10000000,
    IDE_CHANNEL2_NATIVE   = 0b10000001,
    IDE_CHANNEL1_NATIVE   = 0b10000010,
    IDE_CHANNEL_BOTH      = 0b10000011
}_IDENativeModeMask;
typedef enum {
    IDE_CHANNEL_NO_MODIFICATION = 0b01000000,
    IDE_CHANNEL2_MODIFICATION = 0b01000001,
    IDE_CHANNEL1_MODIFICATION = 0b01000010,
    IDE_BOTH_MODIFICATION     = 0b01000011
}_IDEModificationMask;

typedef struct {
    uint8_t nativeModeMask;
    uint8_t modificationMask;
    bool    isBusMaster:1;
}__attribute__((packed)) IDECapabilites;

typedef struct{
    uint16_t IObase;
    uint16_t controlBase;
    uint16_t masterIDE;
    uint16_t noINT;
    uint8_t  INT;
    uint8_t  _PIN;
}__attribute__((packed)) IDEChannel;

typedef struct{
    IDECapabilites     capabilities;
    IDEChannel         channels[2];
    _PCIDeviceDescriptor desc;
}__attribute__((packed)) IDEController;

void setupIDEController(IDEController* c,_PCIDevice* device);
