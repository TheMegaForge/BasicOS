#include "../include/i686/ISR.h"
#include "../include/i686/IDT.h"
#include "../include/isrs.h"
#include "../include/stdio.h"
static InterruptHandler handlers[256] = {0};
extern char** getTB();
unsigned int __attribute__((cdecl)) ISR_HANDLE(Registers* regs){
    if(handlers[regs->interrupt] != (InterruptHandler)0){
        handlers[regs->interrupt](regs);
    }else if(regs->interrupt >= 32){
        char** tb = getTB();
        char* _tb = *tb;
        int written = printf(_tb,"Unhandled Interrupt %d(%x)",CC_WHITE_BLUE,regs->interrupt,regs->interrupt);
        _tb+=(written*2);
        *tb = _tb;
        return 0;
    }else{
        char** tb = getTB();
        printf(tb,"UNHANDLED EXCEPTION! %d",CC_WHITE_RED,regs->interrupt);
        asm("cli");
        asm("hlt");
    }
}

void __attribute__((cdecl)) ISRInitialize(){
    ISRInitializeGates();
    for(int i=0;i<256;i++){
        IDTEnableGate(i);
        handlers[i] = 0;
    }
}

void addInterruptHandler(int interrupt,InterruptHandler handler){
    char** tb = getTB();
    if(handlers[interrupt] != (InterruptHandler)0){
        printf(*tb,"[PANIC]INTERRUPT=%x,%d",CC_WHITE_RED,handlers[interrupt],interrupt);
        asm("cli;hlt");
    }
    handlers[interrupt] = handler;
    IDTEnableGate(interrupt);
}