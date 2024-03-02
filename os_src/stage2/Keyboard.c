#include "include/Keyboard.h"
#include "../include/Driver.h"
extern void writeIO_(StageHandles* sh,uint16_t port,uint8_t data);
void kbd2(StageHandles* sh,uint8_t cmd,uint8_t sub){
    for(int i=0;i<5;i++)
        sh->io_wait();
    writeIO_(sh,KBD_DATA_PORT,cmd);
    for(int i=0;i<5;i++)
        sh->io_wait();
    writeIO_(sh,KBD_DATA_PORT,sub);
    for(int i=0;i<5;i++)
        sh->io_wait();
    
}
static StageHandles* tmp;
void _kbd(Registers* regs);
void _null(Registers* regs){

}
void prepareKeyboard(StageHandles* sh,PS2Device* ps2,Keyboard* kbd){
    if(ps2[0] == PSD_MF_KBD || ps2[1] == PSD_MF_KBD_2){
        sh->IRQRegisterHandler(1,_null);
        tmp = sh;
        writeIO_(sh,KBD_DATA_PORT,0xEE);
        uint8_t _r = readIO_(sh,KBD_DATA_PORT);
        int w = sh->printf(sh->_tb,"_r=%x,",CC_WHITE_BLUE,_r);
        sh->_tb+=(w*2);
        kbd2(sh,0xF0,1);
        _r = readIO_(sh,KBD_DATA_PORT);
        if(_r != 0xFA){
            kbd->scanSet = KBD_SCAN_ERROR;
        }
    }else{
        kbd->okay = false;
        return;
    }
}
extern StageHandles* getHandles();

void createDriver(KBDDriver* drv,Keyboard* kbd,StageHandles* sh){
    if(sh->regDriverINT(PS2_DRV_ID,KBD_DRV_SUB_ID,drv) == CDRV_SUCCESS){
    }else{
        *TEXT_BUFFER = '?';
        sh->kpanic("Keyboard driver allready registered!");
    }
}