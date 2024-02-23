#include "../../include/drivers/AHCI.h"
/*
https://wiki.osdev.org/PCI#Header_Type_0x0
https://wiki.osdev.org/AHCI/ABAR
*/
bool isACHICapable(PCIBus* bus,_PCIDeviceDescriptor* Outdescriptor){
    bool res = 0;
    for(int i=0;i<bus->devices;i++){
        _PCIDevice* device = &bus->PCIDevices[i];
        if(device->class.ClassCode == PC3_MASS_STORAGE_CONTROLLER && device->class.desc.subClassID == 1){
            if(device->DeviceID == 1184 && device->vendorID == 1039){
                Outdescriptor->bus = device->busNum;
                Outdescriptor->slot = device->slotNum;
                Outdescriptor->func = device->funcNum;
                Outdescriptor->ht = device->ht;
                res = true;
                return res;
            }
        }else if(device->class.ClassCode == PC3_MASS_STORAGE_CONTROLLER && device->class.desc.subClassID == 6){
            res = true;
            Outdescriptor->bus = device->busNum;
            Outdescriptor->slot = device->slotNum;
            Outdescriptor->func = device->funcNum;
            Outdescriptor->ht = device->ht;
            return res;
        }
    }
    return res;
}
bool readABAR(_PCIDeviceDescriptor* descriptor){
    if(descriptor->ht != PCI_HT_STANDART/*0*/){
        
    }
    bool res = 0;
}