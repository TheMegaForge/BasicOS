#pragma once
#include "../../include/stdio.h"
#include "../../include/i686/IRQ.h"
#include <stdint.h>
typedef struct{
    int(*printf)(char* tb,char* str,enum _ColorCode cc,...);
    uint8_t(*newLine)(char** sl,uint8_t written,enum _ColorCode cc);
    uint8_t(*puts)(char** tb,char* str,enum _ColorCode cc);
    void(*kpanic)(const char* data);
    void(*setScreenColor)(enum _ColorCode cc);
    uint32_t(*regDriverINT)(int id,int subID,void* addr);
    uint32_t(*getDriverINT)(int id,int subID);
    void (*addInterruptHandler)(int interrupt,InterruptHandler handler);
    void(*IRQRegisterHandler)(int irq,IRQHandler handler);
    uint32_t (*pciConfigReadDWord)(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset);
    uint16_t (*pciConfigReadWord)(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset);
    uint16_t (*readBar16)(uint32_t bar);
    uint32_t (*readBar32)(uint32_t bar);
    int (*strlen)(char* data);
    void (*memcpy)(void* restrict dest,void* restrict src,int size);
    void (*io_wait)();
    void (*outb_)(uint16_t port,uint8_t data);
    void (*outs_)(uint16_t port,uint16_t data);
    void (*outi_)(uint16_t,uint32_t data);
    uint8_t (*inb_)(uint16_t port);
    uint16_t (*ins_)(uint16_t port);
    uint32_t (*ini_)(uint16_t port);
    char* _tb;
}StageHandles;