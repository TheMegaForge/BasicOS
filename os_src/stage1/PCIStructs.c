#include "../include/PCIStructs.h"
#define PC_PREP(spec,sc,subClassesD){.subClassID = sc,.subClasses = subClassesD}
#define PC3_INFO(spec,index)
uint8_t PCIUnclassified[] = {

};

uint8_t PCIMassStorage[] = {

};

uint8_t PCINetworkController[] = {

};

uint8_t PCIDisplayController[] = {

};

uint8_t PCIMultiMediaController[] = {

};

uint8_t PCIMemoryController[] = {

};

uint8_t PCIBridge[] = {

};
uint8_t PCICommunicationController[] = {

};
// BSP = Base System Peripheral
uint8_t PCIBSP[] = {

};

uint8_t PCIInputDeviceController[] = {

};

uint8_t PCIDockingStation[] = {

};

uint8_t PCIProcessor[] = {

};

uint8_t PCISerialBusController[] = {

};

uint8_t PCIWirelessController[] = {

};

uint8_t PCISatelliteCommunicationController[] = {

};

uint8_t PCIEncryptionController[] = {

};

uint8_t PCISignalProcessingController[] = {

};
// 0xFF = NO DATA
uint8_t PCIIntelligentController = 0x0; // I20
uint8_t ProcessingAccelerator = 0xFF;
uint8_t NON_ESSISTANIAL_INSTRUMENT = 0xFF;
uint8_t _0x3F = 0xFF;
uint8_t CoProcessor = 0xFF;
uint8_t _0xFE = 0xFF;
uint8_t UnassignedClassVender = 0xFF;
struct PCIClassDescriptor ClassDescriptors[] = {
    PC_PREP("UNCLASS",0,&PCIUnclassified[0]), //UNCLASS
    PC_PREP("MASS STORAGE",0,&PCIMassStorage[0]),
    PC_PREP("NETWORK CONTROLLER",0,&PCINetworkController[0]),
    PC_PREP("DISPLAY CONTROLLER",0,&PCIDisplayController[0]),
    PC_PREP("MULTIMEDIA CONTROLLER",0,&PCIMultiMediaController[0]),
    PC_PREP("Memory Controller",0,&PCIMemoryController[0]),
    PC_PREP("Bridge",0,&PCIBridge[0]),
    PC_PREP("COMMUNICATION CONTROLLER",0,&PCICommunicationController[0]),
    PC_PREP("Base System Peripheral",0,&PCIBSP[0]),
    PC_PREP("INPUT DEVICE",0,&PCIInputDeviceController[0]),
    PC_PREP("DOCKING STATION",0,&PCIDockingStation[0]),
    PC_PREP("PROCESSOR",0,&PCIProcessor[0]),
    PC_PREP("SERIAL BUS CONTROLLER",0,&PCISerialBusController[0]),
    PC_PREP("WIRELESS CONTROLLER",0,&PCIWirelessController[0]),
    PC_PREP("INTELLIGENT CONTROLLER",0,&PCIIntelligentController),
    PC_PREP("SATELLITE COMMUNICATION CONTROLLER",4,&PCISatelliteCommunicationController[0]),
    PC_PREP("ENCRYPTION CONTROLLER",0,&PCIEncryptionController[0]),
    PC_PREP("SIGNAL PROCESSING CONTROLLER",0,&PCISignalProcessingController[0]),
    PC_PREP("Processing Accelerator",0,&ProcessingAccelerator),
    PC_PREP("Non-Essential Instrumentation",0,&NON_ESSISTANIAL_INSTRUMENT),
    PC_PREP("0x3F(Reserved)",0,&_0x3F),
    PC_PREP("Co-Processor",0,&CoProcessor),
    PC_PREP("0xFE (Reserved)",0,&_0xFE),
    PC_PREP("Unassigned Class (Vendor specific)",0,&UnassignedClassVender)
};
void initPCIClasses(){
    for(uint8_t i = 0;i<0x14;i++){
        struct _PCIClass* class = &pciClasses[i];
        class->ClassCode        = (enum PCIClassCode)i;
        class->desc             = ClassDescriptors[i];
        class->progIfDescriptor = 0;
    }
    struct _PCIClass* class = &pciClasses[0x15];
    class->ClassCode = PC3_CO_PROCESSOR;
    class->desc      = ClassDescriptors[0x15];
    class->progIfDescriptor = 0;
    class++;
    class->ClassCode = PC3__0xFE_RESERVED;
    class->desc      = ClassDescriptors[0x16];
    class->progIfDescriptor = 0;
    class++;
    class->ClassCode = PC3_UNASSIGNED_CLASS_VENDOR_SPECIFIC;
    class->desc      = ClassDescriptors[0x17];
    class->progIfDescriptor = 0;

}
struct _PCIClass pciClasses[0x17] = {
    PC3_INFO("UNCLASSIEFIED",0)//UNCLASSIEFIED
    PC3_INFO("MASS STORAGE",1)
    PC3_INFO("NETWORK CONTROLLER",2)
    PC3_INFO("DISPLAY CONTROLLER",3)
    PC3_INFO("MULTIMEDIA CONTROLLER",4)
    PC3_INFO("MEMORY CONTROLLER",5)
    PC3_INFO("BRIDGE",6)
    PC3_INFO("SIMPLE COMMUNICATION CONTROLLER",7)
    PC3_INFO("BASE SYSTEM PERIPHAEL",8)
    PC3_INFO("INPUT DEVICE CONTROLLER",9)
    PC3_INFO("DOCKING STATION",10)
    PC3_INFO("PROCESSOR",11)
    PC3_INFO("SERIAL BUS CONTROLLER",12)
    PC3_INFO("WIRELESS CONTROLLER",13)
    PC3_INFO("INTELLIGENT CONTROLLER",14)
    PC3_INFO("SATELLITE COMMUNICATION DEVICE",15)
    PC3_INFO("ENCRYPTION CONTROLLER",16)
    PC3_INFO("SIGNAL PROCESSING UNIT",17)
    PC3_INFO("PROCESSING ACCELERATOR",18)
    PC3_INFO("NON ESSENTIAL INSTRUMENT",19)
    PC3_INFO("0x3F(RESERVED)",20)
    PC3_INFO("CO PROCESSOR",21)
    PC3_INFO("0xFE(RESEVED)",22)
    PC3_INFO("UNASSIGNED",23)
};
const uint8_t PCIClassSize = sizeof(struct _PCIClass);