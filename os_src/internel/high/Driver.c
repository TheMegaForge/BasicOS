#include "../../include/Driver.h"
#include "../../include/memdefs.h"
#include "../../include/i686/ISR.h"
#include "../../include/stdio.h"
int32_t* drivers = (int32_t*)0x0000F000;
static int32_t* drvPtr;
static const int32_t* drvLimit = (int32_t*)0x0000F640;
extern uint32_t sysCommon(Registers* regs);
extern char** getTB();
void setupDrivers(){
    drvPtr = &drivers[0];
    addInterruptHandler(60,sysCommon);
}
uint32_t getDriver(Registers* regs){
    if(drvPtr == drvLimit){
        return 0x1000;
    }
    int32_t* drvP = &drivers[0];
    while(drvP != drvPtr){
        if(drvPtr[0] == regs->ecx && drvPtr[1] == regs->ebx){
            return drvPtr[2];
        }
        drvP+=3;
    }
    return CDRV_MISSING;
}
uint32_t registerDriver(Registers* regs){
    if(drvPtr == drvLimit){
        return 0x1000;
    }
    int32_t* drvP = &drivers[0];
    while(drvP != drvPtr){
        if(drvP[0] == regs->ebx){
            return CDRV_ALLREADY_REGISTERED;
        }
        drvP+=3;
    }
    drvP[0] = regs->ebx;//id
    drvP[1] = regs->edx;//subID
    drvP[2] = regs->ecx;//address
    drvPtr+=3;
    return CDRV_SUCCESS;
}
