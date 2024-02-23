#include "../../include/drivers/ATAdrv.h"
#include "../../include/Driver.h"
#include "../../include/stdio.h"
#include "../../include/storage/ATA.h"
#include "../../include/i686/IRQ.h"
CMNStorageError ATAread(void* extraStruct,CMNStorageClusterType ct,
                        uint32_t readCount,uint32_t lba,
                        CMNStorageReturnData* ret,CMNStorageReturnData* extraRet,
                        uint16_t* buffer)
{
    ATAAccess* access = extraStruct;
    bool _ctCanFit = ct < 16;
    return ATAdisk(access->controller,access->primary,true,(_ctCanFit * ct) + (!_ctCanFit*0xFF),readCount,lba,buffer);
}

CMNStorageError ATAwrite(void* extraStruct,CMNStorageClusterType ct,
                        uint32_t writeCount,uint32_t lba,
                        CMNStorageReturnData* ret,CMNStorageReturnData* extraRet,
                        uint16_t* buffer)

{
    ATAAccess* access = extraStruct;
    bool _ctCanFit = ct < 16;
    return ATAdisk(access->controller,access->primary,false,(_ctCanFit * ct) + (!_ctCanFit*0xFF),writeCount,lba,buffer);
}
extern void ATAinterrupt();
void ATAregister(ATAStorage* out){
    uint32_t rv = regDriverINT(CMN_STORAGE_ID,ATA_ID,out);
    if(rv == 0xFFFF){
        kpanic("[ATAdrv]: invalid sysCommon handler called!");
    }else if(rv == CDRV_ALLREADY_REGISTERED){
        kpanic("[ATAdrv]: Allready registered!");
    }else if(rv == 0x1000){
        kpanic("[ATAdrv]: drivers full!");
    }else{
        ATAinterrupt();
        out->ht = DRV_ATA;
        out->read = ATAread;
        out->write = ATAwrite;
    }
}

