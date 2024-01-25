#pragma once
#include "../stdint.h"
typedef struct {
    uint16_t BaseLow;
    uint16_t SegmentSelector;
    uint8_t Reserved;
    uint8_t Flags;
    uint16_t BaseHigh;
}__attribute__((packed)) IDTEntry;

typedef struct {
    uint16_t Limit;
    IDTEntry* entries;
}__attribute__((packed)) IDTDescriptor;

typedef enum {
    IDT_FLAGS_GATE_TASK             = 0x5,
    IDT_FLAGS_GATE_16BIT_INT        = 0x6,
    IDT_FLAGS_GATE_16BIT_TRAP       = 0x7,
    IDT_FLAGS_GATE_32BIT_INT        = 0xE,
    IDT_FLAGS_GATE_32BIT_TRAP       = 0xF,

    IDT_FLAG_RING0                  = (0 << 5),
    IDT_FLAG_RING1                  = (1 << 5),
    IDT_FLAG_RING2                  = (2 << 5),
    IDT_FLAG_RING3                  = (3 << 5),

    IDT_FLAG_PRESENT                = 0x80
}IDT_FLAGS;

void __attribute__((cdecl)) LoadIDT(IDTDescriptor* desc);
void IDTSetGate(int interrupt,void* base,uint16_t segmentDescriptor,uint8_t flags);
void IDTEnableGate(int interrupt);
void IDTDisableGate(int interrupt);
void IDTInitialize();