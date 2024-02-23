#pragma once
#include "i686/ISR.h"
typedef enum{
    CDRV_SUCCESS             = 0,
    CDRV_ALLREADY_REGISTERED = 1,
    CDRV_MISSING             = 2
}DriverINTReturnValue;
extern __attribute__((cdecl)) uint32_t regDriverINT(int id,int subID,void* addr);
extern __attribute__((cdecl)) void*    getDriverINT(int id,int subID);
//uint32_t registerDriver(Registers* regs);
/*
    id = ebx,4
    subID = edx,4
    addr = ecx,4
*/
