#include "../../include/storage/ATA.h"
#include "../../include/i686/io.h"
#include "../../include/i686/irq.h"
#include "../../include/i686/PIC.h"
#include "../../include/stdio.h"

void dskInt(Registers* regs){
    void** info = (void**)regs->eax;
    *(uint32_t*)info[0] = true;
}
void sendDSKEOI(){
    PICSendEndOfInterrupt(2);//clears interrupt flag for master PIC
    PICSendEndOfInterrupt(14);//clears interrupt flag for slave PIC
    PICUnmask(14); // Unmask IRQ14 for ATA
    PICUnmask(2);  // Unmask IRQ2 for the slave PIC
}
