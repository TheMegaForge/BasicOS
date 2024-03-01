#include "../include/HAL.h"
#include "../include/i686/IDT.h"
#include "../include/i686/IRQ.h"
#include "../include/i686/ISR.h"
#include "../include/stdio.h"
extern void initPCIClasses();
extern void setupDrivers();
extern char** getTB();
void HAL_Initilize(ATAController* controller,PCIBus* pciBus,IDEController* ide,StorageCommon* storage){
    char** tb = getTB();
    char* _tb = *tb;
    asm("cli");
    initPCIClasses();
    IDTInitialize();
    ISRInitialize();
    IRQInitialize();
    setupDrivers();
    readPCIBus(pciBus);
    for(int i=0;i<pciBus->devices;i++){
        _PCIDevice* dev = &pciBus->PCIDevices[i];
        if(dev->class.ClassCode == PC3_MASS_STORAGE_CONTROLLER && dev->class.desc.subClassID == 1){
            setupIDEController(ide,dev);
        }
    }
    readATAController(controller,ide);
    ATAregister(storage);
    asm("sti");
}

