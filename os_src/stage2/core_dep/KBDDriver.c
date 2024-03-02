#include "../include/hw/KBDDriver.h"
#include "../include/Keyboard.h"
#include "../../include/Driver.h"
extern StageHandles* _getHandles();
extern char* _drvGetTb(KBDDriver* drv);
extern void _drvIncOrResetInc(const int* ci);
extern void _drvSetBufferFull(const uint8_t* status);
extern void _drvSetHold(const uint8_t* status);
extern void _drvSetReleased(const uint8_t* status);

void __kbd__(Registers* regs){
    *TEXT_BUFFER = 'F';
    StageHandles* sh = _getHandles();
    int w = sh->printf(sh->_tb,"%x,",CC_WHITE_BLUE,sh->inb_(KBD_DATA_PORT));
    sh->_tb+=(w*2);
    /*KBDDriver* drv = _getHandles()->getDriverINT(PS2_DRV_ID,KBD_DRV_SUB_ID);
    if(drv != CDRV_MISSING){
        char* tb = _drvGetTb(drv);
        tb[drv->tb_inc] = _getHandles()->inb_(KBD_DATA_PORT);
        _drvIncOrResetInc(&drv->tb_inc);
        _drvSetBufferFull(&drv->status);
        if((drv->status & 0b10) == 0b10){
            _drvSetReleased(&drv->status);
        }
    }else{
        char* tb = _drvGetTb(drv);
        tb[0] = '\0';
    }*/
}
char8_t await(StageHandles* sh){
    KBDDriver* drv = sh->getDriverINT(PS2_DRV_ID,KBD_DRV_SUB_ID);
    if(drv != CDRV_MISSING){
        while((drv->status & 0b1) == 0b0){
          
        }
    }else{
        return -1;
    }
}
char8_t get(StageHandles* sh){
    return 0;
}
void fgets(StageHandles* sh,char* location,uint8_t length){
    
}