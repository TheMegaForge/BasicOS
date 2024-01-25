#include "../include/stddef.h"
#include "../include/string.h"
#include "../include/stdio.h"
#include "../include/memdefs.h"
#include "../include/NativeTalk.h"
#include "../include/simplealloc.h"
#include "../include/PCI.h"
#include "../include/HAL.h"
#include "../include/i686/math.h"
void(*kernelAddr)(struct KernelTalk* kt) = STAGE_1_LOCATION;
RawFunction __cdecl section(".setup")  void __setup(struct  NativeTalk* nt){
    char* tl = nt->textAddress;
    HAL_Initilize();
    PCIBus bus = {};
    readPCIBus(&bus);
    newLine(&tl,puts(&tl,"SETUP!",CC_WHITE_BLUE),CC_WHITE_BLUE);
    for(int i=0;i<bus.devices;i++){
        if(bus.PCIDevices[i].class.ClassCode == PC3_DISPLAY_CONTROLLER){
            newLine(&tl,puts(&tl,"DISPLAY CONTROLLER!",CC_WHITE_BLUE),CC_WHITE_BLUE);
        }
    }
    //TODO : DO PIC
    if(hasPCI2Mek()){
        kpanic("Can not boot!(PC is too old!)");
    }
    return;
}
