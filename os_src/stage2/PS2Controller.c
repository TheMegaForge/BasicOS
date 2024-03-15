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
uint8_t readIO_Moment(StageHandles* sh,uint16_t port){
    uint8_t status = sh->inb_(KBD_STATUS_PORT);
    if(status & 1 == 0){
        return 0xEE;
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
//extern __cdecl bool probeIfRight(uint8_t fv,uint8_t sv); -------------unused--------------
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
    key->okay = true;
    /*if(res == 0x55){
        key->okay = true;
    }else{
        key->okay = false;
    }*/
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


void detectPS2Devices(StageHandles* sh,PS2Controller* cntrl,PS2Device* devices){
    if(cntrl->okay == false){
        devices[0] = PSD_ERROR;
        devices[1] = PSD_ERROR;
        return;
    }
    if(!cntrl->isDualChannled){
        devices[1] = PSD_NO_DEV;
    }
    if((readIO_(sh,KBD_STATUS_PORT) & 0b1) == 0b1){
        readIO_(sh,KBD_DATA_PORT);
    }
if(cntrl->CRes[0] == PSC_FAIL){
    devices[0] = PSD_ERROR;
    goto dev2;
}
before:
    writeIO_(sh,KBD_DATA_PORT,0xF5);
    uint8_t retVal = readIO_(sh,KBD_DATA_PORT);
    if(retVal == 0xFE){
        goto before;
    }
before2:
    writeIO_(sh,KBD_DATA_PORT,0xF2);
    retVal = readIO_(sh,KBD_DATA_PORT);
    if(retVal == 0xFE){
        goto before2;
    }
    int i = 0;
    uint8_t mem[100];
    while((readIO_(sh,KBD_STATUS_PORT) & 0b01000000) == 0b00000000 & i != 100){
        mem[i] = readIO_Moment(sh,KBD_DATA_PORT);
        i++;
    }
    i = 0;
    while(mem[i] != PSD_BASE && i < 100){
        i++;
    }
    devices[0] = mem[i+1];
before3:
    writeIO_(sh,KBD_DATA_PORT,0xF4);
    for(int i=0;i<10;i++)
        sh->io_wait();
    retVal = readIO_(sh,KBD_DATA_PORT);
    if(retVal == 0xFE){
        goto before3;
    }
//dev 1 ^ 
dev2:
    if(cntrl->isDualChannled){
before4:
        writeSecondPort(sh,0xF5);
        retVal = readIO_(sh,KBD_DATA_PORT);
        if(retVal == 0xFE){
            goto before4;
        }
before5:
        writeSecondPort(sh,0xF2);        
        retVal = readIO_(sh,KBD_DATA_PORT);
        if(retVal == 0xFE){
            goto before5;
        }
        int i = 0;
        for(int i=0;i<100;i++){
            mem[i] = 0;
        }
        while((readIO_(sh,KBD_STATUS_PORT) & 0b01000000) == 0b00000000 & i != 100){
            mem[i] = readIO_Moment(sh,KBD_DATA_PORT);
            i++;
        }
        i = 0;
        while(mem[i] != PSD_BASE && i < 100){
            if(mem[i] == 0){
                devices[1] = 0;
                return;
            }
            i++;
        }
before6:
        devices[0] = mem[i+1];
        writeIO_(sh,KBD_DATA_PORT,0xF4);
        retVal = readIO_(sh,KBD_DATA_PORT);
        if(retVal == 0xFE){
            goto before6;
        }
    }
}


void unlockDevices(StageHandles* sh){
    
}