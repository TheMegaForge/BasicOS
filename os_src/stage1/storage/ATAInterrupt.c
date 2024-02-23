#include "../../include/storage/ATA.h"
#include "../../include/i686/io.h"
#include "../../include/i686/irq.h"
#include "../../include/i686/PIC.h"
#include "../../include/stdio.h"

void dskInt(Registers* regs){
    void** info = (void**)regs->eax;
    *(uint32_t*)info[0] = true;
    uint32_t secs = *(uint32_t*)info[1];
    secs--;
    *(uint32_t*)info[1] = secs;
}
void sendDSKEOI(){
    PICSendEndOfInterrupt(7);
    PICSendEndOfInterrupt(14);
}