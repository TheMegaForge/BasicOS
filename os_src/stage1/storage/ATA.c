#include "../../include/storage/ATA.h"
#include "../../include/i686/io.h"
#include "../../include/i686/irq.h"
#include "../../include/i686/PIC.h"
#include "../../include/stdio.h"
#define writeCommandRegister(iobase,data) writeIORegisterByte(iobase,7,data)

uint8_t readIORegister(uint16_t base,uint8_t reg){
    uint8_t data = inb_(base+reg);
    io_wait();
    return data;
}

uint8_t readStatusRegister(uint16_t base){
    return readIORegister(base,7);
}

void writeIORegisterByte(uint16_t base,uint8_t reg,uint8_t data){    
    outb_(base+reg,data);
    for(int i=0;i<14;i++)
        io_wait();
    
    while(readStatusRegister(base) & 0b10000000 == 0b10000000){}
}


void writeIORegisterWord(uint16_t base,uint8_t reg,uint16_t data){    
    outs_(base+reg,data);

    for(int i=0;i<14;i++)
        io_wait();
    
    while(readStatusRegister(base) & 0b10000000 == 0b10000000){}
}
char* statusT = TEXT_BUFFER;
extern char** getTB();
void ATAidentify(IDEChannel* ata,ATAInformation* info,_CATAValidation* validation,bool isSlave){
    char** tb = getTB();
    char* _tb = *tb;
    uint16_t ident[256] = {0};
    printf(_tb,"ata-controlBase=%x",CC_WHITE_BLUE,ata->controlBase);
    if(isSlave){
        writeIORegisterByte(ata->IObase,6,0xB0);   
    }else{
        writeIORegisterByte(ata->IObase,6,0xA0);       
    }
    writeIORegisterByte(ata->IObase,3,0);
    writeIORegisterByte(ata->IObase,4,0);
    writeIORegisterByte(ata->IObase,5,0);
    writeCommandRegister(ata->IObase,0xEC);
    for(int i=0;i<15;i++)
        io_wait();
    
    int8_t status = readStatusRegister(ata->IObase);
    if(status == 0){
        *statusT = 'Q';
        statusT+=2;
        return;
        if(*validation & ATA_VALIDATION_MASTER0 == ATA_VALIDATION_MASTER0 && isSlave){
           *validation = (*validation ^ ATA_VALIDATION_MASTER0); 
        }else{
            if(*validation & ATA_VALIDATION_SLAVE0 == ATA_VALIDATION_SLAVE0){
                *validation = (*validation ^ ATA_VALIDATION_SLAVE0);
            }
        }
    }
    while(status & 0b10000000 == 0b10000000){
        status = readStatusRegister(ata->IObase);
    }

    if(readIORegister(ata->IObase,4) != 0 && (readIORegister(ata->IObase,5) != 0)){

    }else{
        int8_t status = readStatusRegister(ata->IObase);               
        while(status & 3 == 3){
            status = readStatusRegister(ata->IObase);
        }
    }
    while(readStatusRegister(ata->IObase) & 8 != 8 );
    for(int i=0;i<257;i++){
        ident[i] = ins_(ata->IObase/*data register*/);
        //TODO: TEST IF DRQ!! && LATER!
    }

    info->isHardDrive               = (bool)ident[0];
    info->supports48LBA             = ident[83] & (1 << 10) == (1 << 10);
    info->supportedUDMA_Models      = ident[88] & 0x00FF;
    info->activeUDMA_Model          = ident[88] & 0xFF00 >> 8;
    info->detected80ConductorCable  = ident[93] & (1 << 11) == (1 << 11);
    info->maxLBA28                  = *(uint32_t*)&ident[60];
    info->MaxLba48.upper            = *(uint32_t*)&ident[100];
    info->MaxLba48.lower            = ident[103];
}
extern void ATAVerify(uint16_t iobase1,uint16_t iobase2,_CATAValidation* validation);
void readATAController(ATAController* ata,IDEController* ide){
    char** tb = getTB();
    char* _tb = *tb;
    if(getDriverINT(CMN_STORAGE_ID,ATA_ID) == CDRV_MISSING){
        if(regDriverINT(CMN_STORAGE_ID,ATA_ID,ata) == CDRV_SUCCESS){
            ata->master0 = ide->channels[0];
            ata->slave0 = ide->channels[1];
            if(readStatusRegister(ata->master0.IObase) != 0xFF){
                ata->validation = (ata->validation|ATA_VALIDATION_MASTER0);
            }
            if(readStatusRegister(ata->slave0.IObase) != 0xFF){
                ata->validation = (ata->validation|ATA_VALIDATION_SLAVE0);
            }
            ATAidentify(&ata->master0,&ata->info[0],&ata->validation,false);
            ATAidentify(&ata->slave0,&ata->info[1],&ata->validation,true);


            //INFO: DOES WORK!
            //TODO: DO IDENTIFCATION COMMAND (wiki.osdev.org/ATA **PIO MODE**)
        }
    }else{
        kpanic("[ATA]:Driver Allready exits!");
    }
}
extern void dskInt(Registers* regs);
void ATAinterrupt(){
    IRQRegisterHandler(14,dskInt);
    IRQRegisterHandler(15,dskInt);
}
void diskCommon(IDEChannel* disk,bool primary,uint32_t lba,uint16_t sectorNumber,ATAInformation* info){
    uint8_t pb = 0;
    if(primary){
        pb = 0xE0;
    }else{
        pb = 0xF0;
    }
    writeIORegisterByte(disk->IObase,6,pb|((lba>>24) & 0x0F));
    writeIORegisterByte(disk->IObase,1,0);
    writeIORegisterByte(disk->IObase,2,(uint8_t)sectorNumber);
    writeIORegisterByte(disk->IObase,3,(uint8_t)lba);
    writeIORegisterByte(disk->IObase,4,(uint8_t)(lba >> 8));
    writeIORegisterByte(disk->IObase,5,(uint8_t)(lba >> 16));
};
#include "../../include/i686/io.h"
extern __attribute__((cdecl)) void movEAX(uint32_t data);
extern __attribute__((cdecl)) void dskRead(void** intInfo);
void readContent(void** contentInfo){
    uint16_t* buffer = (uint16_t*)contentInfo[2];
    uint16_t base    = *(uint16_t*)contentInfo[3];
    for(int i=0;i<257;i++){
        uint16_t value = ins_(base);
        for(int j=0;j<14;j++)
            io_wait();
        *buffer = value;
        buffer++;
    }
}
CMNStorageError ATAdisk(ATAController* controller,bool primary,bool read,uint32_t SecPerClu,uint32_t clusters,uint32_t lba,uint16_t* buffer){
    uint32_t secs = SecPerClu*clusters;
    char** tb = getTB();
    char* _tb = *tb;
    if(SecPerClu == 0xFF){
        return CSE_TO_LARGE_SECTORS;
    }
    if(SecPerClu == 0){
        return CSE_TO_TINY_SECTORS;
    }
    if(buffer < 0x00007BFF){
        return CSE_INVALID_PTR;
    }
    IDEChannel* channel = (IDEChannel*)0x0;
    ATAInformation* info = (ATAInformation*)0x0;
    if(primary){
        channel = &controller->master0;
        info = &controller->info[0];
    }else{
        channel = &controller->slave0;
        info = &controller->info[1];
    }
    diskCommon(channel,primary,lba,secs,info);
    uint32_t isReady = false;
    int w = printf(_tb,"is Ready=%x,secs=%x,buffer=%x,iobase=%x",CC_WHITE_BLUE,&isReady,&secs,buffer,&channel->IObase);
    _tb+=(w*2);
    *tb = _tb;
    uint32_t CSecs = secs;
    void* intInfo[] = {&isReady,&CSecs,buffer,&channel->IObase};
    if(read){
        writeCommandRegister(channel->IObase,0x20);//READ_CMD
        dskRead(&intInfo);
    }
    return CSE_SUCCESS;
}