#include "../include/i686/IRQ.h"
#include "../include/i686/ISR.h"
#include "../include/i686/PIC.h"
#include "../include/i686/io.h"
#include "../include/stdio.h"
#define PIC_REMAP_OFFSET 0x20
IRQHandler IRQHandlers[16];
char** getTB();
uint32_t IRQ_COMMON(Registers* regs);
void IRQInitialize(){
    PICConfigure(PIC_REMAP_OFFSET,PIC_REMAP_OFFSET+8);
    for(int i=0;i<16;i++){
        addInterruptHandler(PIC_REMAP_OFFSET+i,IRQ_COMMON);
    }
    enableInterrupts();
}
uint32_t IRQ_COMMON(Registers* regs){
    int status = 1;
    int irq = regs->interrupt-PIC_REMAP_OFFSET;
    uint8_t pic_isr = PICReadInServiceRegister();
    uint8_t pic_irr = PICReadIRQRequestRegisters();
    if(IRQHandlers[irq] != (IRQHandler)0){
        IRQHandlers[irq](regs);
        status = 0;
    }else{
        char** tb = getTB();
        char* _tb = *tb;
        int w = printf(_tb,"UHI = %d,ISR=%d,IRR=%d",CC_WHITE_RED,irq,pic_isr,pic_irr);
        _tb+=(w*2);
        *tb = _tb;
        newLine(tb,w,CC_WHITE_RED);
        status = 2;
    }
    PICSendEndOfInterrupt(irq);
    return status;
}
void IRQRegisterHandler(int irq,IRQHandler handler){
    IRQHandlers[irq] = handler;
}