
#include "../include/stddef.h"
#include "../include/string.h"
#include "../include/stdio.h"
#include "../include/memdefs.h"
#include "../include/NativeTalk.h"
#include "../include/simplealloc.h"
#include "../include/PCI.h"
#include "../include/HAL.h"
#include "../include/i686/math.h"
#include "../include/utils/binary.h"
#include "../include/i686/ISR.h"
#include "../include/i686/IRQ.h"
static char* _tb;
char** getTB(){
    return &_tb;
}
void timer(Registers* regs){
    _tb = putc(_tb,'.',CC_WHITE_RED);
}
#define SETUP_COLOR CC_WHITE_BLUE
extern int isrTest();
void(*kernelAddr)(struct KernelTalk* kt) = STAGE_1_LOCATION;
RawFunction __cdecl section(".setup")  void __setup(struct  NativeTalk* nt){
    _tb = nt->textAddress;
    PCIBus bus = {};
    int w = puts(&_tb,"SETUP! Started",CC_WHITE_RED);
    newLine(&_tb,w,CC_WHITE_BLUE);
    HAL_Initilize(&bus);
    w = puts(&_tb,"SETUP! Ended",CC_WHITE_RED);
    newLine(&_tb,w,CC_WHITE_BLUE);
    asm("sti");
    IRQRegisterHandler(0,timer);
    while(true){
        
    }
    return;
}

