#include "../include/i686/IDT.h"
#include "../include/utils/binary.h"
IDTEntry g_IDT[256];
IDTDescriptor g_IDTDesc = {sizeof(g_IDT)-1,g_IDT};
void __attribute__((cdecl)) LoadIDT(IDTDescriptor* desc);


void IDTSetGate(int interrupt,void* base,uint16_t segmentDescriptor,uint8_t flags){
    g_IDT[interrupt].BaseLow = ((uint32_t)base) & 0xFFFF;
    g_IDT[interrupt].SegmentSelector = segmentDescriptor;
    g_IDT[interrupt].Reserved = 0;
    g_IDT[interrupt].Flags = flags;
    g_IDT[interrupt].BaseHigh = ((uint32_t)base >>  16) & 0xFFFF;
}
void IDTEnableGate(int interrupt){
    FLAG_SET(g_IDT[interrupt].Flags,IDT_FLAG_PRESENT);
}
void IDTDisableGate(int interrupt){
    FLAG_UNSET(g_IDT[interrupt].Flags,IDT_FLAG_PRESENT);
}
void IDTInitialize(){
    LoadIDT(&g_IDTDesc);
    for(int i=0;i<255;i++){
        IDTEnableGate(i);
    }
}