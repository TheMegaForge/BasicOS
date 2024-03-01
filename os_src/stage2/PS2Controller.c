#include "include/PS2Controller.h"
#include "include/bits.h"
void writeIO_(StageHandles* sh,uint16_t port,uint8_t data){
    uint8_t status = sh->inb_(KBD_STATUS_PORT);
    while(status & 0b10 == 0b10 ){
        status = sh->inb_(KBD_STATUS_PORT);
    }
    sh->outb_(port,data);
}
uint8_t readIO_(StageHandles* sh,uint16_t port){
    uint8_t status = sh->inb_(KBD_STATUS_PORT);
    while(status & 1 == 0 ){
        status = sh->inb_(KBD_STATUS_PORT);
    }
    return sh->inb_(port);
}
uint8_t readCMD(StageHandles* sh,uint8_t cmd){
    writeIO_(sh,KBD_COMMAND_PORT,cmd);
    return readIO_(sh,KBD_DATA_PORT);
}
void writeFirstPort(StageHandles* sh,uint8_t data){
    writeIO_(sh,KBD_DATA_PORT,data);
    for(int i=0;i<14;i++){
        sh->io_wait();
    }
}
void writeSecondPort(StageHandles* sh,uint8_t data){
    writeIO_(sh,KBD_COMMAND_PORT,0xD4);
    writeIO_(sh,KBD_DATA_PORT,data);
}
extern __cdecl bool probeIfRight(uint8_t fv,uint8_t sv);
void InstallPS2(StageHandles* sh,PS2Controller* key){
    sh->outb_(KBD_COMMAND_PORT,0xAD);
    sh->outb_(KBD_COMMAND_PORT,0xA7);
    uint8_t status = sh->inb_(KBD_STATUS_PORT);
    while(status & 1 == 1){
        uint8_t d = sh->inb_(KBD_DATA_PORT);
        status = sh->inb_(KBD_STATUS_PORT);
    }
    uint8_t oldVal = readCMD(sh,0x20);
    key->isDualChannled = (oldVal & 0b00100000 == 0b00100000);
    oldVal = bitClear8(oldVal,0);
    oldVal = bitClear8(oldVal,1);
    oldVal = bitClear8(oldVal,6);
    writeIO_(sh,KBD_COMMAND_PORT,0x60);
    writeIO_(sh,KBD_DATA_PORT,oldVal);
    int wrote = 0;
    uint8_t res = 0;
    while((res != 0x55 || res != 0xFC) && wrote < 100){
        res = readCMD(sh,0xAA);
        wrote++;
    }
    if(res == 0x55){
        key->okay = true;
    }else{
        key->okay = false;
    }
    writeIO_(sh,KBD_COMMAND_PORT,0x60);
    writeIO_(sh,KBD_DATA_PORT,oldVal);
    
    key->probeRes[0] = readCMD(sh,0xAB);
    if(key->okay){
        writeIO_(sh,KBD_COMMAND_PORT,0xAE);
        oldVal|=1;
    }
    if(!key->isDualChannled){
        key->probeRes[1] = KPR_NO_RESULT;
    }else{
        writeIO_(sh,KBD_COMMAND_PORT,0xA8);
        key->probeRes[1] = readCMD(sh,0xA9);
        oldVal|=0b10;
    }

    if(!key->isDualChannled){
        key->probeRes[1] = KPR_NO_RESULT;
    }else{
        writeIO_(sh,KBD_COMMAND_PORT,0xA8);
        key->probeRes[1] = readCMD(sh,0xA9);
        oldVal|=0b10;
    }
    if(key->okay){
        writeIO_(sh,KBD_COMMAND_PORT,0x60);
        writeIO_(sh,KBD_DATA_PORT,oldVal);
    }

    writeIO_(sh,KBD_DATA_PORT,0xFF);
    uint8_t r1 = (readIO_(sh,KBD_DATA_PORT)-0xFA);
    uint8_t r2 = (readIO_(sh,KBD_DATA_PORT)-0xAA);
    if(r1 == 0 && r2 == 0){
        key->CRes[0] = PSC_BOTH;
    }else if(r2 != 0){
        key->CRes[0] = PSC_FAIL;
    }else{
        key->CRes[0] = PSC_NO_DEVICE;
    }
    if(key->isDualChannled){
        writeSecondPort(sh,0xFF);
        r1 = (readIO_(sh,KBD_DATA_PORT)-0xFA);
        r2 = (readIO_(sh,KBD_DATA_PORT)-0xAA);
        if(r1 == 0 && r2 == 0){
            key->CRes[1] = PSC_BOTH;
        }else if(r2 != 0){
            key->CRes[1] = PSC_FAIL;
        }else{
            key->CRes[1] = PSC_NO_DEVICE;
        }
    }   
}

