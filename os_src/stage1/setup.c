
#include "../include/stddef.h"
#include "../include/string.h"
#include "../include/stdio.h"
#include "../include/memdefs.h"
#include "../include/NativeTalk.h"
#include "../include/PCI.h"
#include "../include/HAL.h"
#include "../include/i686/math.h"
#include "../include/utils/binary.h"
#include "../include/i686/ISR.h"
#include "../include/i686/IRQ.h"
#include "../include/switch/DiskInfo.h"
static char* _tb = 0;
char** getTB(){
    return &_tb;
}
void timer(Registers* regs){

}
void key(Registers* regs){
    puts(&_tb,"KEY!",CC_WHITE_BLUE);
}
void switch_d(Registers* regs){

}
#define SETUP_COLOR CC_WHITE_BLUE
extern int isrTest();
#define KERNEL_SECTORS 2

RawFunction __cdecl section(".setup")  void __setup(struct  NativeTalk* nt){
    _tb = nt->textAddress;
    PCIBus        bus = {};
    IDEController ide = {};
    ATAController ata = {};
    StorageCommon storage = {};
    HAL_Initilize(&ata,&bus,&ide,&storage);
    {
        int w = 0;
        newLine(&_tb,puts(&_tb,"IDE CHANNELS0/1->",CC_WHITE_BLUE),CC_WHITE_BLUE);
        w = printf(_tb,"\tCHANNEL0,IOBase=%x,CntrBase=%x,INT=%d,MID=%d",CC_WHITE_BLUE,ide.channels[0].IObase,ide.channels[0].controlBase,ide.channels[0].INT,ide.channels[0].masterIDE);
        _tb+=(w*2);
        newLine(&_tb,w,CC_WHITE_BLUE);
        w = printf(_tb,"\tCHANNEL1,IOBase=%x,CntrBase=%x,INT=%d,MID=%d",CC_WHITE_BLUE,ide.channels[1].IObase,ide.channels[1].controlBase,ide.channels[1].INT,ide.channels[1].masterIDE);
        _tb+=(w*2);
        newLine(&_tb,w,CC_WHITE_BLUE);
    }
    IRQRegisterHandler(0,timer);
    IRQRegisterHandler(1,key);
    int w = printf(_tb,"ATAInfo: max LBA28 = %d,max LBA48(upper) = %d,lower = %d",CC_WHITE_BLUE,ata.info[0].maxLBA28,ata.info[0].MaxLba48.upper,ata.info[0].MaxLba48.lower);
    _tb+=(w*2);
    newLine(&_tb,w,CC_WHITE_BLUE);
    w = printf(_tb,"    HDD=%bb,LBA48=%bb",CC_WHITE_BLUE,ata.info[0].isHardDrive,ata.info[0].supports48LBA);
    _tb+=(w*2);
    newLine(&_tb,w,CC_WHITE_BLUE);
    ATAAccess access = {};
    access.primary = true;
    access.controller = &ata;
    uint32_t maxLBAMemory_lower = (ata.info[0].maxLBA28/2)*512;
    uint32_t maxLBAMemory_upper = (ata.info[0].maxLBA28/2)*512;
    uint32_t KIB_lower = maxLBAMemory_lower/1024;
    uint32_t KIB_upper = maxLBAMemory_upper/1024;
    uint32_t MIB_lower = KIB_lower/1024;
    uint32_t MIB_upper = KIB_upper/1024;
    uint32_t totalMIBS = MIB_lower+MIB_upper;
    uint32_t totalGIBS = totalMIBS/1024;
    uint32_t totalKIBS = KIB_upper+KIB_lower;
    w = printf(_tb,"Total Storage in 1024 Format:",CC_WHITE_BLUE);
    _tb+=(w*2);
    newLine(&_tb,w,CC_WHITE_BLUE);
    w = printf(_tb,"     KIB=%d,MIB=%d,GIB~=%d,raw_lower=%d,raw_upper=%d",CC_WHITE_BLUE,totalKIBS,totalMIBS,totalGIBS,KIB_lower,KIB_upper);
    _tb+=(w*2);
    newLine(&_tb,w,CC_WHITE_BLUE);
    if(storage.read(&access,CCT_4048,1,4,0,0,STAGE_2_LOCATION) == CSE_SUCCESS){
        addInterruptHandler(100,switch_d);
        void(*stage2)(DiskInfo*,PCIBus*,StorageInfo*,char*) = STAGE_2_LOCATION;
        DiskInfo dInfo = {&ide,&ata,&storage};
        StorageInfo si = {&totalGIBS,&totalMIBS,&totalKIBS};
        stage2(&dInfo,&bus,&si,_tb);
    }else{
        puts(&_tb,"CAN NOT BOOT!READING STAGE2 FAILED!",CC_WHITE_BLUE);
        
    }
    for(;;){}
    return;
}

