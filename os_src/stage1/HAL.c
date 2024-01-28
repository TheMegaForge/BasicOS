#include "../include/HAL.h"
#include "../include/i686/IDT.h"
#include "../include/i686/IRQ.h"
#include "../include/i686/ISR.h"
extern void initPCIClasses();
void HAL_Initilize(PCIBus* pciBus){
    asm("cli");
    initPCIClasses();
    IDTInitialize();
    ISRInitialize();
    IRQInitialize();
    readPCIBus(pciBus);
}

