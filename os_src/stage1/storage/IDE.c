#include "../../include/storage/IDE.h"
#include "../../include/utils/binary.h"
#include "../../include/stdio.h"
extern char** getTB();

void setupIDEController(IDEController* c,_PCIDevice* device){
    uint8_t progIF = device->class.progIfDescriptor;
    IDECapabilites* caps = &c->capabilities;
    caps->nativeModeMask = IDE_CHANNEL_NO_NATIVE;
    caps->nativeModeMask = (caps->nativeModeMask|(IDE_CHANNEL1_NATIVE*(progIF==0b1)));
    caps->nativeModeMask = (caps->nativeModeMask|(IDE_CHANNEL2_NATIVE*(progIF==0b100)));
    caps->modificationMask = IDE_CHANNEL_NO_MODIFICATION;
    caps->modificationMask = (caps->modificationMask|(IDE_CHANNEL1_MODIFICATION*(progIF==0b10)));
    caps->modificationMask = (caps->modificationMask|(IDE_CHANNEL2_MODIFICATION*(progIF==0b1000)));
    if(caps->nativeModeMask == IDE_CHANNEL_BOTH){
        IDEChannel* _c = &c->channels[0];
        _c->IObase      = (uint16_t)readBar16(pciConfigReadDWord(device->busNum,device->slotNum,device->funcNum,0x10));
        _c->controlBase = (uint16_t)readBar16(pciConfigReadDWord(device->busNum,device->slotNum,device->funcNum,0x14));
        _c->masterIDE   = (uint16_t)readBar16(pciConfigReadDWord(device->busNum,device->slotNum,device->funcNum,0x20));
        _c->noINT       = false;
        uint16_t intpin = (uint32_t)readBar32(pciConfigReadDWord(device->busNum,device->slotNum,device->funcNum,0x3C)) & 0x0000FFFF;
        _c->INT         = (intpin & 0x00FF);
        _c->_PIN        = (intpin & 0xFF00) >> 8;
        _c++;
        intpin = (uint32_t)readBar32(pciConfigReadDWord(device->busNum,device->slotNum,device->funcNum,0x3C)) & 0x0000FFFF;
        _c->INT         = (intpin & 0xFF00) >> 8;
        _c->_PIN        = (intpin & 0x00FF);
        _c->IObase      = (uint16_t)readBar16(pciConfigReadDWord(device->busNum,device->slotNum,device->funcNum,0x18));
        _c->controlBase = (uint16_t)readBar16(pciConfigReadDWord(device->busNum,device->slotNum,device->funcNum,0x1C));
        _c->masterIDE   = (uint16_t)readBar16(pciConfigReadDWord(device->busNum,device->slotNum,device->funcNum,0x20));
        _c->noINT       = false;
    }else if(caps->nativeModeMask == IDE_CHANNEL_NO_NATIVE){
        IDEChannel * _c = &c->channels[0];
        _c->IObase      = 0x1F0;
        _c->controlBase = 0x3F6;
        _c->masterIDE   = (progIF==0b10000000)*(uint16_t)readBar16(pciConfigReadDWord(device->busNum,device->slotNum,device->funcNum,0x20));
        _c->noINT       = false;
        _c->INT         = 14;
        _c->_PIN        = 0xFE;
        _c++;
        _c->IObase      = 0x170;
        _c->controlBase = 0x376;
        _c->masterIDE   = (progIF==0b10000000)*(uint16_t)readBar16(pciConfigReadDWord(device->busNum,device->slotNum,device->funcNum,0x20));
        _c->noINT       = false;
        _c->INT         = 15;
        _c->_PIN        = 0xFE;
    }else{
        if(caps->nativeModeMask != IDE_CHANNEL1_NATIVE && caps->nativeModeMask != IDE_CHANNEL2_NATIVE){//means in campability mode (ports 0x1F0-0x1F7, 0x3F6, IRQ14).
            IDEChannel* _c  = &c->channels[0];
            _c->IObase      = 0x1F0;
            _c->controlBase = 0x3F6;
            _c->masterIDE   = (progIF==0b10000000)*(uint16_t)readBar16(pciConfigReadDWord(device->busNum,device->slotNum,device->funcNum,0x20));
            _c->noINT       = false;
            _c->INT         = 14;
            _c->_PIN        = 0xFE;
        }else{
            IDEChannel* _c  = &c->channels[0];
            _c->IObase      = (uint16_t)readBar16(pciConfigReadDWord(device->busNum,device->slotNum,device->funcNum,0x10));
            _c->controlBase = (uint16_t)readBar16(pciConfigReadDWord(device->busNum,device->slotNum,device->funcNum,0x14));
            _c->masterIDE   = (uint16_t)readBar16(pciConfigReadDWord(device->busNum,device->slotNum,device->funcNum,0x20));
            _c->noINT       = false;
        }
        if(caps->nativeModeMask != IDE_CHANNEL2_NATIVE){
            IDEChannel* _c  = &c->channels[1];
            _c->IObase      = 0x170;
            _c->controlBase = 0x376;
            _c->masterIDE   = (progIF==0b10000000)*(uint16_t)readBar16(pciConfigReadDWord(device->busNum,device->slotNum,device->funcNum,0x20));
            _c->noINT       = false;
            _c->INT         = 15;
            _c->_PIN        = 0xFE;
        }else{
            IDEChannel* _c  = &c->channels[0];
            _c->IObase      = (uint16_t)readBar16(pciConfigReadDWord(device->busNum,device->slotNum,device->funcNum,0x18));
            _c->controlBase = (uint16_t)readBar16(pciConfigReadDWord(device->busNum,device->slotNum,device->funcNum,0x1C));
            _c->masterIDE   = (uint16_t)readBar16(pciConfigReadDWord(device->busNum,device->slotNum,device->funcNum,0x20));
            _c->noINT       = false;
        }
    }
}
