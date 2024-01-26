#include "../include/HAL.h"
#include "../include/i686/IDT.h"
//#include "../include/i686/PIC.h"
#include "../include/i686/ISR.h"
extern void initPCIClasses();
void HAL_Initilize(PCIBus* pciBus){
    initPCIClasses();
    IDTInitialize();
    //ISRInitialize();
    readPCIBus(pciBus);
}

