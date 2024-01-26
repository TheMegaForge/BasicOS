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
static char* _tb;
void(*kernelAddr)(struct KernelTalk* kt) = STAGE_1_LOCATION;
RawFunction __cdecl section(".setup")  void __setup(struct  NativeTalk* nt){
    _tb = nt->textAddress;
    getUIntVarArg(&nt,1);
    volatile register char f = *(char*)PRINTF_NUMBER_BEG;
    printf(_tb,"Num Data: %u",CC_GREEN_BLUE,1000);

    return;
}
