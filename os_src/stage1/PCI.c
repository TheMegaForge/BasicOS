#include "../include/PCI.h"
#include "../include/i686/math.h"
#include "../include/i686/io.h"
#include "../include/utils/binary.h"
#include "../include/memdefs.h"
#include "../include/stdio.h"
#include "../include/string.h"
void assignPCIDeviceHeader(_PCIDevice* device,uint32_t ClassProgIF){
    uint16_t Class = extractWordFromDWord(ClassProgIF,true);
    uint8_t class = extractByteFromWord(Class,true);
    uint8_t Subclass = extractByteFromWord(Class,false);
    device->class = pciClasses[class];
    device->class.desc->subClassID = Subclass;
}

typedef struct {
    _PCIDevice* beg;//0
    uint32_t current;
    uint8_t bus;
    uint8_t slot;
}__attribute__((packed)) PCIIterator;
bool hasPCI2Mek(){
    uint16_t* isMK2 = (uint16_t*)0x7BFE;
    uint16_t data = *isMK2;
    data = data >>15;
    return (bool)data;
}
uint32_t pciConfigReadDWord(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset){
    uint32_t address;
    uint32_t lbus  = (uint32_t)bus;
    uint32_t lslot = (uint32_t)slot;
    uint32_t lfunc = (uint32_t)func;
    address = (uint32_t)((lbus << 16) | (lslot << 11) |
              (lfunc << 8) | (offset & 0xFC) | ((uint32_t)0x80000000));
    outi_(CONFIG_ADDR_PORT, address);
    return ini_(DATA_ADDR_PORT);
}
uint16_t pciConfigReadWord(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset){
    return (uint16_t)(pciConfigReadDWord(bus,slot,func,offset) >> ((offset & 2) * 8) & 0xFFFF);
}
bool readPCIDeviceInfo(PCIIterator* iterator,uint8_t func,uint32_t* statusCommand,uint32_t* ClassProgIF,uint32_t* Bist_HT_Latency_CacheLineSize){
    uint32_t verif = pciConfigReadDWord(iterator->bus,iterator->slot,func,0);
    *statusCommand = pciConfigReadDWord(iterator->bus,iterator->slot,func,4);
    *ClassProgIF = pciConfigReadDWord(iterator->bus,iterator->slot,func,8);
    *Bist_HT_Latency_CacheLineSize = pciConfigReadDWord(iterator->bus,iterator->slot,func,0xC);
    return verif != 0xFFFFFFFF;
}
uint8_t readPCIDeviceFunctions(PCIIterator* iterator){
    uint8_t devices = 0;
    for(uint8_t i=0;i<8;i++){
        uint32_t statusCommand = 0;
        uint32_t ClassProgIF = 0;
        uint32_t BistHTLatency_CacheLineSize = 0;
        if(readPCIDeviceInfo(iterator,i,&statusCommand,&ClassProgIF,&BistHTLatency_CacheLineSize)){
            _PCIDevice* device = &iterator->beg[iterator->current];
            device->busNum  = iterator->bus;
            device->slotNum = iterator->slot;
            device->funcNum = i;
            device->command = (statusCommand & 0x0000FFFF);
            device->status  = (statusCommand & 0xFFFF0000) >> 16;
            assignPCIDeviceHeader(device,ClassProgIF);
            volatile int tmp = 0;
            volatile register struct _PCIClass CLS = device->class;
            tmp++;
            volatile register uint8_t subClass     = device->class.desc->subClassID;
            tmp++;
            iterator->current++;
            devices++;
        }else{

        }
    }
    return devices;
}
bool readPCIDevice(uint8_t* detectedDevices,PCIIterator* iterator,_PCIDevice** Output){
    uint32_t statusCommand = 0;
    uint32_t ClassProgIF = 0;
    uint32_t BistHTLatency_CacheLineSize = 0;
    if(Output != (void*)0xFF && *Output != (void*)0){
        kpanic("readPCIDevice : Output is nonzero!");
    }
    if(readPCIDeviceInfo(iterator,0,&statusCommand,&ClassProgIF,&BistHTLatency_CacheLineSize)){
        _PCIDevice* device = &iterator->beg[iterator->current];
        device->busNum = iterator->bus;
        device->slotNum = iterator->slot;
        device->funcNum = 0;
        device->command = (statusCommand & 0x0000FFFF);
        device->status  = ((statusCommand & 0xFFFF0000));
        device->status = device->status >> 16;
        uint32_t HT  = (BistHTLatency_CacheLineSize & 0x00FF0000);
        HT = HT >> 16;
        device->ht = (enum PCIHeaderType)HT;
        if((HT >> 7) == 1){
           *detectedDevices = readPCIDeviceFunctions(iterator);
        }
        assignPCIDeviceHeader(device,ClassProgIF);
        volatile int tmp = 0;
        volatile register struct _PCIClass CLS = device->class;
        tmp++;
        volatile register uint8_t subClass     = device->class.desc->subClassID;
        tmp++;
        iterator->current++;
        *Output = device;
        return true;
    }else{
        *Output = 0xFFFF0000;
        return false;
    }
}
uint8_t PCIScanSlotLine(PCIIterator* iterator){
    iterator->slot = 0;
    uint8_t deviceCount = 0;
    for(int i=0;i<32;i++){
        iterator->slot = i;
        uint8_t detectedDevices = 0;
        if(readPCIDevice(&detectedDevices,iterator,0xFF)){
            deviceCount++;
            deviceCount+=detectedDevices;
        }
    }
    iterator->slot = 0;
    return deviceCount;
}
void readPCIBus(PCIBus* pci){
    pci->PCIDevices = PCI_BUSSES_BEGIN;
    PCIIterator iterator = {};
    iterator.beg = PCI_BUSSES_BEGIN;
    iterator.bus = 0;
    iterator.slot = 0;
    iterator.current = 0;
    uint32_t statusCommand  = 0;
    uint32_t ClassProgIF    = 0;
    uint32_t BistHT         = 0;
    for(int i=0;i<256;i++){
        iterator.bus = i;
        pci->devices+=PCIScanSlotLine(&iterator);
    }
    return;
}