
#pragma once
/*
    --------------------------------------------------
    //COMMENTS FROM WEBSITE https://wiki.osdev.org/PCI
    --------------------------------------------------
*/
#include "stdint.h"
#include "stdbool.h"
extern const uint8_t PCIClassSize;
#define DECOMPRESSED 
#define SPACED_COMPRESSED //when its larger than the compressed version and some bitfiels are getting used
#define LIST_CONTROLL   //when a list is descriped using some bitfields.
DECOMPRESSED __attribute__((packed)) struct PCIBarMemory{
    uint16_t upper31_4_bits;
    uint16_t lower31_4_bits;
    bool prefatch;
    uint8_t type;   //2 bits
    bool alwaysZero;
};
DECOMPRESSED __attribute__((packed)) struct PCIBarIO{
    uint32_t bits31_2;
    bool reserved;
    bool always1;
};
//When you want to retrieve the actual base address of a BAR, be sure to mask the lower bits. For 16-bit Memory Space BARs, you calculate (BAR[x] & 0xFFF0). For 32-bit Memory Space BARs, you calculate (BAR[x] & 0xFFFFFFF0). 
//For 64-bit Memory Space BARs, you calculate ((BAR[x] & 0xFFFFFFF0) + ((BAR[x + 1] & 0xFFFFFFFF) << 32)) For I/O Space BARs, you calculate (BAR[x] & 0xFFFFFFFC).
//Before attempting to read the information about the BAR, make sure to disable both I/O and memory decode in the command byte. You can restore the original value after completing the BAR info read. 
//This is needed as some devices are known to decode the write of all ones to the register as an (unintended) access.
//To determine the amount of address space needed by a PCI device, you must save the original value of the BAR, write a value of all 1's to the register, then read it back. The amount of memory can then be determined by masking the information bits, performing a bitwise NOT ('~' in C), and incrementing the value by 1. The original value of the BAR should then be restored. The BAR register is naturally aligned and as such you can only modify the bits that are set. 
//For example, if a device utilizes 16 MB it will have BAR0 filled with 0xFF000000 (0x1000000 after decoding) and you can only modify the upper 8-bits. [1]

DECOMPRESSED __attribute__((packed)) struct PCIBistReg{
    bool isCapable;//will return on if supported
    bool startBist;//1 = bits.start(),if started gets reseted,IF NOT COMPLETE AFTER 2 SECONDS SHOULD BE FAILED BY SW!
    uint8_t reserved;//bits 4-5
    uint8_t completionCode;//will return 0,after bist execution,if the test completed successfully
};
enum PCIHeaderType{
    PCI_HT_STANDART = 0x0,
    PCI_HT_PCI_BRIDGE = 0x1,
    PCI_HT_CARDBUS_BRIDGE = 0x2
};
DECOMPRESSED __attribute__((packed)) struct PCIHeaderTypeReg{
    bool hasMultipleFunctions;//1 bit
    enum PCIHeaderType type;//7 bits
};
DECOMPRESSED __attribute__((packed)) struct PCICommandRegister{
    uint8_t bits15_11_reserved;
    bool interruptDisabled; 
    bool fastBackToBack;
    bool serrEnabled;
    bool reserved;
    bool parityErrorResponse;
    bool vgaPalletSnoop;
    bool MemoryWriteAndInvalidateEnable;
    bool SpecialCycles;
    bool BusMaster;
    bool MemorySpace;
    bool IOSpace;
};
//Interrupt Disable - If set to 1 the assertion of the devices INTx# signal is disabled; otherwise, assertion of the signal is enabled.
//Fast Back-Back Enable - If set to 1 indicates a device is allowed to generate fast back-to-back transactions; otherwise, fast back-to-back transactions are only allowed to the same agent.
//SERR# Enable - If set to 1 the SERR# driver is enabled; otherwise, the driver is disabled.
//Bit 7 - As of revision 3.0 of the PCI local bus specification this bit is hardwired to 0. In earlier versions of the specification this bit was used by devices and may have been hardwired to 0, 1, or implemented as a read/write bit.
//Parity Error Response - If set to 1 the device will take its normal action when a parity error is detected; otherwise, when an error is detected, the device will set bit 15 of the Status register (Detected Parity Error Status Bit), but will not assert the PERR# (Parity Error) pin and will continue operation as normal.
//VGA Palette Snoop - If set to 1 the device does not respond to palette register writes and will snoop the data; otherwise, the device will trate palette write accesses like all other accesses.
//Memory Write and Invalidate Enable - If set to 1 the device can generate the Memory Write and Invalidate command; otherwise, the Memory Write command must be used.
//Special Cycles - If set to 1 the device can monitor Special Cycle operations; otherwise, the device will ignore them.
//Bus Master - If set to 1 the device can behave as a bus master; otherwise, the device can not generate PCI accesses.
//Memory Space - If set to 1 the device can respond to Memory Space accesses; otherwise, the device's response is disabled.
//I/O Space - If set to 1 the device can respond to I/O Space accesses; otherwise, the device's response is disabled.
//If the kernel configures the BARs of the devices, the kernel also have to enable bits 0 and 1 for it to activate.
DECOMPRESSED __attribute__((packed)) struct PCIStatusRegister{
    bool detectedParityError;
    bool signaledSystemError;
    bool RecievedMasterAbort;
    bool RecievedTargetAbort;
    bool SignaledTargetAbort;
    bool DEVSLTiming;
    bool MasterDataParityError;
    bool FastBackToBackCapable;
    bool Reserved;
    bool _66MHZCapable;
    bool CapabiliesList;
    bool InterruptStatus;
    uint8_t reserved;//2 bits
};
//Detected Parity Error - This bit will be set to 1 whenever the device detects a parity error, even if parity error handling is disabled.
//Signalled System Error - This bit will be set to 1 whenever the device asserts SERR#.
//Received Master Abort - This bit will be set to 1, by a master device, whenever its transaction (except for Special Cycle transactions) is terminated with Master-Abort.
//Received Target Abort - This bit will be set to 1, by a master device, whenever its transaction is terminated with Target-Abort.
//Signalled Target Abort - This bit will be set to 1 whenever a target device terminates a transaction with Target-Abort.
//DEVSEL Timing - Read only bits that represent the slowest time that a device will assert DEVSEL# for any bus command except Configuration Space read and writes. Where a value of 0x0 represents fast timing, a value of 0x1 represents medium timing, and a value of 0x2 represents slow timing.
//Master Data Parity Error - This bit is only set when the following conditions are met. The bus agent asserted PERR# on a read or observed an assertion of PERR# on a write, the agent setting the bit acted as the bus master for the operation in which the error occurred, and bit 6 of the Command register (Parity Error Response bit) is set to 1.
//Fast Back-to-Back Capable - If set to 1 the device can accept fast back-to-back transactions that are not from the same agent; otherwise, transactions can only be accepted from the same agent.
//Bit 6 - As of revision 3.0 of the PCI Local Bus specification this bit is reserved. In revision 2.1 of the specification this bit was used to indicate whether or not a device supported User Definable Features.
//66 MHz Capable - If set to 1 the device is capable of running at 66 MHz; otherwise, the device runs at 33 MHz.
//Capabilities List - If set to 1 the device implements the pointer for a New Capabilities Linked list at offset 0x34; otherwise, the linked list is not available.
//Interrupt Status - Represents the state of the device's INTx# signal. If set to 1 and bit 10 of the Command register (Interrupt Disable bit) is set to 0 the signal will be asserted; otherwise, the signal will be ignored.
// PC3 = PCCC = PCI Class Code
enum PCIClassCode{
    PC3_UNCLASSIFIED                        = 0,
    PC3_MASS_STORAGE_CONTROLLER             = 1,
    PC3_NETWORK_CONTROLLER                  = 2,
    PC3_DISPLAY_CONTROLLER                  = 3,
    PC3_MULTIMEDIA_CONTROLLER               = 4,
    PC3_MEMORY_CONTROLLER                   = 5,
    PC3_BRIDGE                              = 6,
    PC3_SIMPLE_COMMUNICATION_CONTROLLER     = 7,
    PC3_BASE_SYSTEM_PERIPHALE               = 8,
    PC3_INPUT_DEVICE_CONTROLLER             = 9,
    PC3_DOCKING_STATION                     = 0xA,
    PC3_PROCESSOR                           = 0xB,
    PC3_SERIAL_BUS_CONTROLLER               = 0xC,
    PC3_WIRELESS_CONTROLLER                 = 0xD,
    PC3_INTELLIGENT_CONTROLLER              = 0xE,
    PC3_SATELLITE_COMMUNICATION_DEVICE      = 0xF,
    PC3_ENCRYPTION_CONTROLLER               = 0x10,
    PC3_SIGNAL_PROCESSING_UNIT              = 0x11,
    PC3_PROCESSING_ACCELERATOR              = 0x12,
    PC3_NON_ESSENTIAL_INSTRUMENT            = 0x13,
    PC3__0x3F_RESERVED                      = 0x14,
    PC3_CO_PROCESSOR                        = 0x40,
    PC3__0xFE_RESERVED                      = 0x41,
    PC3_UNASSIGNED_CLASS_VENDOR_SPECIFIC    = 0xFF
};
__attribute__((packed)) struct PCIClassDescriptor{
    uint8_t subClassID;
    uint8_t* subClasses;
};
__attribute__((packed)) struct _PCIClass{
    enum PCIClassCode ClassCode;
    struct PCIClassDescriptor* desc;
    uint8_t progIfDescriptor;//upper 4 = type,lower 4 = index
};
extern struct _PCIClass pciClasses[];