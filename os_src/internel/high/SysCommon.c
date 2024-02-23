#include "../../include/i686/ISR.h"
static const int sysCommonSubCalls = 1;
extern __attribute__((cdecl)) uint32_t registerDriver(Registers* reg);
extern __attribute__((cdecl)) uint32_t getDriver(Registers* reg);
uint32_t sysCommon(Registers* regs){
    uint32_t(*subCalls[])(Registers* regs) = {registerDriver,getDriver};
    if(regs->eax > sysCommonSubCalls){
        return 0xFFFF;
    }
    return subCalls[regs->eax](regs);
}