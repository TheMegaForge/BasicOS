#pragma once
#include "ISR.h"
typedef void(*IRQHandler)(Registers* regs);
void IRQInitialize();
void IRQRegisterHandler(int irq,IRQHandler handler);