#pragma once
#include <stdint.h>
void PICInitialize();
void PICUnmask(int irq);
void PICMask(int irq);
void PICDisable();
void PICSendEndOfInterrupt(int irq);
void PICConfigure(uint8_t offsetPic1,uint8_t offsetPic2);
uint16_t PICReadIRQRequestRegisters();
uint16_t PICReadInServiceRegister();