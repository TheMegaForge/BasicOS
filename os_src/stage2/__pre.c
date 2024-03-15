#include "../include/stddef.h"
#include "../include/switch/DiskInfo.h"
#include "../include/PCI.h"
#include "../include/stdio.h"
#include "../include/memdefs.h"
#include "include/SwitchHandles.h"
#include "include/PS2Controller.h"
#include "include/Keyboard.h"
#include "include/hw/KBDDriver.h"
#include "include/MLL.h"
#include "include/string.h"
//RFS = refined file system
#include "fs/RFSCore.h"
#include "include/x86.h"
#include <stdint.h>
int index = 0;
static StageHandles* sh;
static KBDDriver kbd_drv = {};
__cdecl void _pstart(DiskInfo* dsk ,PCIBus* bus ,StorageInfo* storage,char* _tb){
    PS2Controller _ps2 = {};
    PS2Device _psd[2] = {};
    StageHandles h = {};
    Keyboard kbd = {};
    Regions regions = {};
    uint32_t usableMBs = 0;
    uint32_t totalMBs = 0;
    pre__init(&_ps2,&_psd[0],&h,_tb,&kbd);
    int w = h.printf(h._tb,"Memory: Regions=%d",CC_WHITE_BLUE,getNumberOfLayouts());
    h._tb+=(w*2);
    h.newLine(&h._tb,w,CC_WHITE_BLUE);
    if(getNumberOfLayouts() >= 20){
        h.kpanic("MEMORY: TOO MANY REGIONS");
    }
    fetchRegions(&regions);
    int _reg = getNumberOfLayouts();
    usableMBs = regions.info.usableMemory/1000000;
    totalMBs  = regions.info.totalMemory/1000000;
    if(usableMBs == totalMBs){
        usableMBs-=5;
    }
    w = h.printf(h._tb,"Memory: Usable Memory = %d MB Total Memory = %d MB",CC_WHITE_BLUE,usableMBs,totalMBs);
    h._tb+=(w*2);
    h.newLine(&h._tb,w,CC_WHITE_BLUE);
    if(usableMBs < 512){
        h.kpanic("NOT ENOUGH MEMORY, 512 MB REQUIRED");
    }
    char cmd[200];
    uint8_t cnt = 0;
    char* addr = h.LineToScreenAddress(22+1)+(12*2);
    fgets_opi(&cmd[0],&cnt,&addr,CC_WHITE_BLUE);
    if(strncmp(&cmd[0],"fetch",5)==0){
        enterFetch(&h,dsk,storage);
    }
    for(;;){};
}
void enterFetch(StageHandles* sh,DiskInfo* dsk,StorageInfo* info){
    ATAAccess access = {};
    access.primary = true;
    access.controller = dsk->dskCntrl;
    sh->setScreenColor(CC_BLACK_BLUE);
    sh->_tb = 0xb8000;
    int w = sh->printf(sh->_tb,"[MSG/Fetch]: Fetch Started!",CC_BLACK_WHITE);
    sh->_tb+=(w*2);
    sh->newLine(&sh->_tb,w,CC_BLACK_BLUE);
    w = sh->printf(sh->_tb,"[MSG/FS]: Checking if RFS is present and working",CC_BLACK_WHITE);
    sh->_tb+=(w*2);
    sh->newLine(&sh->_tb,w,CC_BLACK_WHITE);
    uint16_t rfs_info[256];
    CMNStorageError se = dsk->cmnStorage->read(&access,CCT_512,1,info->t_maxLBA28-1,0,0,&rfs_info[0]);
    if(rfs_info[0] == 0){
        w = sh->printf(sh->_tb,"  \\ ----> NO!",CC_BLACK_RED);
        sh->_tb+=(w*2);
        sh->newLine(&sh->_tb,w,CC_BLACK_WHITE);
        //TODO : FS DOES NOT EXITS!
    }
}
KBDDriver* getKBD(){
    return &kbd_drv;
}
void pre__init(PS2Controller* _ps2,PS2Device* _psd,StageHandles* __sh,char* _tb,Keyboard* kbd){
    //TODO : NOT FINISHED
    void* _f[20] = {};
    getHandles(&_f[0]);
    setupHandles(__sh,&_f[0]);
    __sh->_tb = _tb;
    int w = __sh->puts(&__sh->_tb,"started Stage2 (PreBoot)",CC_WHITE_BLUE);
    __sh->newLine(&__sh->_tb,w,CC_WHITE_BLUE);
    displayBoot(__sh);
    asm("cli");
    InitalizePS2(_ps2,_psd,__sh);
    asm("sti");
    InitalizeKeyboard(__sh,kbd,_psd);
    sh = __sh;
}
void displayBoot(StageHandles* sh){
    uint8_t (*onLine)(uint16_t line,char* data,enum _ColorCode cc) = 0x00000b5c;
    onLine(23,"Console >>>",CC_WHITE_BLUE);
}
void InitalizePS2(PS2Controller* _ps2,PS2Device* _psd,StageHandles* sh){
    installPs2Handlers(sh);
    InstallPS2(sh,_ps2);
    bool fo = false;
    bool so = false;
    if(_ps2->isDualChannled && _ps2->okay){
        fo = true;
    }
    if(_ps2->probeRes[0] == KPR_PASSED && _ps2->probeRes[1] == KPR_PASSED){
        so = true;
    }else if(_ps2->probeRes[0] != KPR_PASSED && _ps2->probeRes[1] != KPR_PASSED){
        so = 0;
    }else{
        so = 2;
    }
    int w = sh->printf(sh->_tb,"PS2: %bb %be ",CC_WHITE_BLUE,fo,so);
    sh->_tb+=(w*2);
    sh->newLine(&sh->_tb,w,CC_WHITE_BLUE);
    detectPS2Devices(sh,_ps2,_psd);
    w = sh->printf(sh->_tb,"PS2: Device Types = %x,%x",CC_WHITE_BLUE,_psd[0],_psd[1]);
    sh->_tb+=(w*2);
    sh->newLine(&sh->_tb,w,CC_WHITE_BLUE);
}
extern void __kbd__(Registers* regs);
void InitalizeKeyboard(StageHandles* handles,Keyboard* kbd,PS2Device* devs){
    prepareKeyboard(handles,devs,kbd);
    handles->IRQRegisterHandler(1,__kbd__);
    createDriver(&kbd_drv,kbd,handles);
}
StageHandles* _getHandles(){
    return sh;
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
    sh->IRQRegisterHandler  = _f[8];
    sh->pciConfigReadDWord  = _f[9];
    sh->pciConfigReadWord   = _f[10];
    sh->readBar16           = _f[11];
    sh->readBar32           = _f[12];
    sh->strlen              = _f[13];
    sh->memcpy              = _f[14];
    sh->io_wait             = _f[15];
    sh->inb_                = 0x00004597;
    sh->ins_                = _f[17];
    sh->outb_               = _f[18];
    sh->outs_               = _f[19];
    sh->ini_                = 0x000045b2;
    sh->outi_               = 0x00004585;
    sh->LineToScreenAddress = 0x00000bdb;
}
void irq12(Registers* regs){
    
}
void key(Registers* regs){

}
void installPs2Handlers(StageHandles* sh){
    sh->IRQRegisterHandler(12,irq12);
    sh->IRQRegisterHandler(1,key);
}