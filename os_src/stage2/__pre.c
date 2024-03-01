#include "../include/stddef.h"
#include "../include/switch/DiskInfo.h"
#include "../include/PCI.h"
#include "../include/stdio.h"
#include "../include/memdefs.h"
#include "include/SwitchHandles.h"
#include "include/PS2Controller.h"
#include "include/x86.h"
#include <stdint.h>
__cdecl void _pstart(DiskInfo* dsk ,PCIBus* bus ,StorageInfo* storage,char* _tb){
    void* _f[20] = {};
    PS2Controller _ps2 = {};
    getHandles(&_f[0]);
    StageHandles h = {};
    setupHandles(&h,&_f[0]);
    h._tb = _tb;
    int w = h.puts(&h._tb,"Stage2 entered!",CC_WHITE_BLUE);
    h.newLine(&h._tb,w,CC_WHITE_BLUE);
    displayBoot(&h);
    asm("cli");
    installPs2Handlers(&h);
    InstallPS2(&h,&_ps2);
    bool fo = false;
    bool so = false;
    if(_ps2.isDualChannled && _ps2.okay){
        fo = true;
    }
    if(_ps2.probeRes[0] == KPR_PASSED && _ps2.probeRes[1] == KPR_PASSED){
        so = true;
    }else if(_ps2.probeRes[0] != KPR_PASSED && _ps2.probeRes[1] != KPR_PASSED){
        so = 0;
    }else{
        so = 2;
    }
    w = h.printf(h._tb,"PS2: %bb %be ",CC_WHITE_BLUE,fo,so);
    h._tb+=(w*2);
    h.newLine(&h._tb,w,CC_WHITE_BLUE);
    for(;;){};
}
void displayBoot(StageHandles* sh){
    uint8_t (*onLine)(uint16_t line,char* data,enum _ColorCode cc) = 0x00000acc;
    onLine(23,"Console >>>",CC_WHITE_BLUE);
}
void setupHandles(StageHandles* sh,void** _f){
    sh->printf         = _f[0];
    sh->newLine        = _f[1];
    sh->puts           = _f[2];
    sh->kpanic         = _f[3];
    sh->setScreenColor = _f[4];
    sh->regDriverINT   = _f[5];
    sh->getDriverINT   = _f[6];
    sh->addInterruptHandler = _f[7];
    sh->IRQRegisterHandler = _f[8];
    sh->pciConfigReadDWord = _f[9];
    sh->pciConfigReadWord  = _f[10];
    sh->readBar16          = _f[11];
    sh->readBar32          = _f[12];
    sh->strlen             = _f[13];
    sh->memcpy             = _f[14];
    sh->io_wait            = _f[15];
    sh->inb_               = _f[16];
    sh->ins_               = _f[17];
    sh->outb_              = _f[18];
    sh->outs_              = _f[19];
    sh->ini_               = 0x00004434;
    sh->outi_              = 0x00004415;
}
void irq12(Registers* regs){
    
}
void installPs2Handlers(StageHandles* sh){
    sh->IRQRegisterHandler(12,irq12);
}