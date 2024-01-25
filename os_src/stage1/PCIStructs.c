#include "../include/PCIStructs.h"
#define PC_PREP(spec,sc,subClassesD){.subClassID = sc,.subClasses = subClassesD}
#define PC3_PREP(spec,cc,index){.ClassCode = cc,.desc = &ClassDescriptors[index]}
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
    PC_PREP("UNCLASS",0,&PCIUnclassified[0]),
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
struct _PCIClass pciClasses[] = {
    PC3_PREP("UNCLASSIFIED",PC3_UNCLASSIFIED,0),
    PC3_PREP("MASS STORAGE",PC3_MASS_STORAGE_CONTROLLER,1),
    PC3_PREP("NETWORK CONTROLLER",PC3_NETWORK_CONTROLLER,2),
    PC3_PREP("DISPLAY CONTROLLER",PC3_DISPLAY_CONTROLLER,3),
    PC3_PREP("MULTIMEDIA CONTROLLER",PC3_MULTIMEDIA_CONTROLLER,4),
    PC3_PREP("MEMORY CONTROLLER",PC3_MEMORY_CONTROLLER,5),
    PC3_PREP("BRIDGE",PC3_BRIDGE,6),
    PC3_PREP("SIMPLE COMMUNICATION CONTROLLER",PC3_SIMPLE_COMMUNICATION_CONTROLLER,7),
    PC3_PREP("BASE SYSTEM PERIPHAEL",PC3_BASE_SYSTEM_PERIPHALE,8),
    PC3_PREP("INPUT DEVICE CONTROLLER",PC3_INPUT_DEVICE_CONTROLLER,9),
    PC3_PREP("DOCKING STATION",PC3_DOCKING_STATION,0xA),
    PC3_PREP("PROCESSOR",PC3_PROCESSOR,0xB),
    PC3_PREP("SERIAL BUS CONTROLLER",PC3_SERIAL_BUS_CONTROLLER,0xC),
    PC3_PREP("WIRELESS CONTROLLER",PC3_WIRELESS_CONTROLLER,0xD),
    PC3_PREP("INTELLIGENT CONTROLLER",PC3_INTELLIGENT_CONTROLLER,0xE),
    PC3_PREP("SATELLITE COMMUNICATION DEVICE",PC3_SATELLITE_COMMUNICATION_DEVICE,0xF),
    PC3_PREP("ENCRYPTION CONTROLLER",PC3_ENCRYPTION_CONTROLLER,0x10),
    PC3_PREP("SIGNAL PROCESSING UNIT",PC3_SIGNAL_PROCESSING_UNIT,0x11),
    PC3_PREP("PROCESSING ACCELERATOR",PC3_PROCESSING_ACCELERATOR,0x12),
    PC3_PREP("NON ESSENTIAL INSTRUMENT",PC3_NON_ESSENTIAL_INSTRUMENT,0x13),
    PC3_PREP("0x3F(RESERVED)",PC3__0x3F_RESERVED,0x14),
    PC3_PREP("CO PROCESSOR",PC3_CO_PROCESSOR,0x15),
    PC3_PREP("0xFE(RESEVED)",PC3__0xFE_RESERVED,0x16),
    PC3_PREP("UNASSIGNED",PC3_UNASSIGNED_CLASS_VENDOR_SPECIFIC,0x17),
};
const uint8_t PCIClassSize = sizeof(struct _PCIClass);