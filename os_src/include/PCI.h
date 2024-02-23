#pragma once
#include "i686/io.h"
#include "PCIStructs.h"
#define CONFIG_ADDR_PORT 0xCF8
#define DATA_ADDR_PORT 0xCFC 
/*
    attachment = 
    00000000 => invalid
    00010000 => (VALIDATION BIT!) & INVALID
    11010011 => bits 31-16,15-8 are connected                           (W)
    11010001 => bits 31-16 are connected,15-8,7-0 are seperate          (W)
    11110001 => bits 31-8 are connected,7-0 are seperate                (W)
    00111000 => all seperated                                           (W)
    11111111 => all connected                                           (W)
*/
enum AttachmentBits{
    ATTB_INVALID                        = 0x0,
    ATTB_INVALID_TYPE_2                 = 0b00010000,
    ATTB_ALL_CONNECTED                  = 0b11111111,
    ATTB_ALL_SEPERATED                  = 0b00111000,
    ATTB_2_2_CONNECTED                  = 0b11010011,
    ATTB_2_CONNECTED_2_SEPERATED        = 0b11010001,
    ATTB_3_CONNECTED_1_SEPERATED        = 0b11110001
};
__attribute__((packed)) struct PCIHeader{
    uint8_t reg;
    uint8_t offset;
    uint8_t attachment;
};
//TODO : ADD STATUS & COMMAND REGISTER INFORMATION AS STRUCT AND DOCUMENT IT!
__attribute__((packed)) struct PCIHeaderDescriptor{
    uint8_t count;
    struct PCIHeader* headers;
};
extern struct PCIHeaderDescriptor headers[3];
uint16_t pciConfigReadWord(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset);
uint32_t pciConfigReadDWord(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset);
typedef struct {
    uint8_t busNum;
    uint8_t slotNum;
    uint8_t funcNum;
    uint16_t status;
    uint16_t command;
    enum PCIHeaderType ht;
    struct _PCIClass class;
    uint16_t vendorID;
    uint16_t DeviceID;
}__attribute__((packed)) _PCIDevice;

typedef struct {
    uint8_t hasMassStorage;
    uint8_t hasDisplayController;
    uint8_t hasNetworkController;
    uint8_t hasKeyboard;
    uint8_t hasMouse;

    uint8_t numberOfMassStorages;
    uint8_t NumberOfDisplayControllers;
}__attribute__((packed)) PCIFineInformation;
typedef struct {
    int devices;
    _PCIDevice* PCIDevices;
    PCIFineInformation information;
}__attribute__((packed)) PCIBus;
void readPCIBus(PCIBus* pci);
bool hasPCI2Mek();
uint16_t readBar16(uint32_t bar);
uint32_t readBar32(uint32_t bar);