#include "../include/PCIStructs.h"
#define PC_PREP(spec,sc,subClassesD){.subClassID = sc,.subClasses = subClassesD}
#define PC3_INFO(spec,index)
/*
0x0 - Unclassified	0x0 - Non-VGA-Compatible Unclassified Device	--
0x1 - VGA-Compatible Unclassified Device	--
0x1 - Mass Storage Controller	0x0 - SCSI Bus Controller	--
0x1 - IDE Controller	0x0 - ISA Compatibility mode-only controller
0x5 - PCI native mode-only controller
0xA - ISA Compatibility mode controller, supports both channels switched to PCI native mode
0xF - PCI native mode controller, supports both channels switched to ISA compatibility mode
0x80 - ISA Compatibility mode-only controller, supports bus mastering
0x85 - PCI native mode-only controller, supports bus mastering
0x8A - ISA Compatibility mode controller, supports both channels switched to PCI native mode, supports bus mastering
0x8F - PCI native mode controller, supports both channels switched to ISA compatibility mode, supports bus mastering
0x2 - Floppy Disk Controller	--
0x3 - IPI Bus Controller	--
0x4 - RAID Controller	--
0x5 - ATA Controller	0x20 - Single DMA
0x30 - Chained DMA
0x6 - Serial ATA Controller	0x0 - Vendor Specific Interface
0x1 - AHCI 1.0
0x2 - Serial Storage Bus
0x7 - Serial Attached SCSI Controller	0x0 - SAS
0x1 - Serial Storage Bus
0x8 - Non-Volatile Memory Controller	0x1 - NVMHCI
0x2 - NVM Express
0x80 - Other	--
0x2 - Network Controller	0x0 - Ethernet Controller	--
0x1 - Token Ring Controller	--
0x2 - FDDI Controller	--
0x3 - ATM Controller	--
0x4 - ISDN Controller	--
0x5 - WorldFip Controller	--
0x6 - PICMG 2.14 Multi Computing Controller	--
0x7 - Infiniband Controller	--
0x8 - Fabric Controller	--
0x80 - Other	--
0x3 - Display Controller	0x0 - VGA Compatible Controller	0x0 - VGA Controller
0x1 - 8514-Compatible Controller
0x1 - XGA Controller	--
0x2 - 3D Controller (Not VGA-Compatible)	--
0x80 - Other	--
0x4 - Multimedia Controller	0x0 - Multimedia Video Controller	--
0x1 - Multimedia Audio Controller	--
0x2 - Computer Telephony Device	--
0x3 - Audio Device	--
0x80 - Other	--
0x5 - Memory Controller	0x0 - RAM Controller	--
0x1 - Flash Controller	--
0x80 - Other	--
0x6 - Bridge	0x0 - Host Bridge	--
0x1 - ISA Bridge	--
0x2 - EISA Bridge	--
0x3 - MCA Bridge	--
0x4 - PCI-to-PCI Bridge	0x0 - Normal Decode
0x1 - Subtractive Decode
0x5 - PCMCIA Bridge	--
0x6 - NuBus Bridge	--
0x7 - CardBus Bridge	--
0x8 - RACEway Bridge	0x0 - Transparent Mode
0x1 - Endpoint Mode
0x9 - PCI-to-PCI Bridge	0x40 - Semi-Transparent, Primary bus towards host CPU
0x80 - Semi-Transparent, Secondary bus towards host CPU
0x0A - InfiniBand-to-PCI Host Bridge	--
0x80 - Other	--
0x7 - Simple Communication Controller	0x0 - Serial Controller	0x0 - 8250-Compatible (Generic XT)
0x1 - 16450-Compatible
0x2 - 16550-Compatible
0x3 - 16650-Compatible
0x4 - 16750-Compatible
0x5 - 16850-Compatible
0x6 - 16950-Compatible
0x1 - Parallel Controller	0x0 - Standard Parallel Port
0x1 - Bi-Directional Parallel Port
0x2 - ECP 1.X Compliant Parallel Port
0x3 - IEEE 1284 Controller
0xFE - IEEE 1284 Target Device
0x2 - Multiport Serial Controller	--
0x3 - Modem	0x0 - Generic Modem
0x1 - Hayes 16450-Compatible Interface
0x2 - Hayes 16550-Compatible Interface
0x3 - Hayes 16650-Compatible Interface
0x4 - Hayes 16750-Compatible Interface
0x4 - IEEE 488.1/2 (GPIB) Controller	--
0x5 - Smart Card Controller	--
0x80 - Other	--
0x8 - Base System Peripheral	0x0 - PIC	0x0 - Generic 8259-Compatible
0x1 - ISA-Compatible
0x2 - EISA-Compatible
0x10 - I/O APIC Interrupt Controller
0x20 - I/O(x) APIC Interrupt Controller
0x01 - DMA Controller	0x00 - Generic 8237-Compatible
0x01 - ISA-Compatible
0x02 - EISA-Compatible
0x02 - Timer	0x00 - Generic 8254-Compatible
0x01 - ISA-Compatible
0x02 - EISA-Compatible
0x03 - HPET
0x3 - RTC Controller	0x0 - Generic RTC
0x1 - ISA-Compatible
0x4 - PCI Hot-Plug Controller	--
0x5 - SD Host controller	--
0x6 - IOMMU	--
0x80 - Other	--
0x9 - Input Device Controller	0x0 - Keyboard Controller	--
0x1 - Digitizer Pen	--
0x2 - Mouse Controller	--
0x3 - Scanner Controller	--
0x4 - Gameport Controller	0x0 - Generic
0x10 - Extended
0x80 - Other	--
0xA - Docking Station	0x0 - Generic	--
0x80 - Other	--
0xB - Processor	0x0 - 386	--
0x1 - 486	--
0x2 - Pentium	--
0x3 - Pentium Pro	--
0x10 - Alpha	--
0x20 - PowerPC	--
0x30 - MIPS	--
0x40 - Co-Processor	--
0x80 - Other	--
0xC - Serial Bus Controller	0x0 - FireWire (IEEE 1394) Controller	0x0 - Generic
0x10 - OHCI
0x1 - ACCESS Bus Controller	--
0x2 - SSA	--
0x3 - USB Controller	0x0 - UHCI Controller
0x10 - OHCI Controller
0x20 - EHCI (USB2) Controller
0x30 - XHCI (USB3) Controller
0x80 - Unspecified
0xFE - USB Device (Not a host controller)
0x4 - Fibre Channel	--
0x5 - SMBus Controller	--
0x6 - InfiniBand Controller	--
0x7 - IPMI Interface	0x0 - SMIC
0x1 - Keyboard Controller Style
0x2 - Block Transfer
0x8 - SERCOS Interface (IEC 61491)	--
0x9 - CANbus Controller	--
0x80 - Other	--
0xD - Wireless Controller	0x0 - iRDA Compatible Controller	--
0x1 - Consumer IR Controller	--
0x10 - RF Controller	--
0x11 - Bluetooth Controller	--
0x12 - Broadband Controller	--
0x20 - Ethernet Controller (802.1a)	--
0x21 - Ethernet Controller (802.1b)	--
0x80 - Other	--
0xE - Intelligent Controller	0x0 - I20	--
0xF - Satellite Communication Controller	0x1 - Satellite TV Controller	--
0x2 - Satellite Audio Controller	--
0x3 - Satellite Voice Controller	--
0x4 - Satellite Data Controller	--
0x10 - Encryption Controller	0x0 - Network and Computing Encrpytion/Decryption	--
0x10 - Entertainment Encryption/Decryption	--
0x80 - Other	--
0x11 - Signal Processing Controller	0x0 - DPIO Modules	--
0x1 - Performance Counters	--
0x10 - Communication Synchronizer	--
0x20 - Signal Processing Management	--
0x80 - Other	--
0x12 - Processing Accelerator	--	--
0x13 - Non-Essential Instrumentation	--	--
0x14 - 0x3F (Reserved)	--	--
0x40 - Co-Processor	--	--
0x41 - 0xFE (Reserved)	--	--
0xFF - Unassigned Class (Vendor specific)	--*/
uint8_t PCIUnclassified[] = {
    0,
    1
};

uint8_t PCIMassStorage[] = {
    0,
    1,
    2,
    3,
    4,
    5,
    6,
    7,
    8,
    0x80
};

uint8_t PCINetworkController[] = {
    0,
    1,
    2,
    3,
    4,
    5,
    6,
    7,
    8,
    0x80
};

uint8_t PCIDisplayController[] = {
    0,
    1,
    2,
    0x80
};

uint8_t PCIMultiMediaController[] = {
    0,
    1,
    2,
    3,
    4,
    0x80
};

uint8_t PCIMemoryController[] = {
    0,
    1,
    0x80
};

uint8_t PCIBridge[] = {
    0,
    1,
    2,
    3,
    4,
    5,
    6,
    7,
    8,
    9,
    0xA,
    0x80
};
uint8_t PCICommunicationController[] = {
    0,
    1,
    2,
    4,
    5,
    0x80
};
// BSP = Base System Peripheral
uint8_t PCIBSP[] = {
    0,
    1,
    2,
    3,
    4,
    5,
    6,
    0x80
};

uint8_t PCIInputDeviceController[] = {
    0,
    1,
    2,
    3,
    4,
    0x80
};

uint8_t PCIDockingStation[] = {
    0,
    0x80
};

uint8_t PCIProcessor[] = {
    0,
    1,
    2,
    3,
    0x10,
    0x20,
    0x30,
    0x40,
    0x80
};

uint8_t PCISerialBusController[] = {
    0,
    1,
    2,
    3,
    4,
    5,
    6,
    7,
    8,
    9,
    0x80
};

uint8_t PCIWirelessController[] = {
    0,
    1,
    0x10,
    0x11,
    0x12,
    0x20,
    0x21,
    0x80
};

uint8_t PCISatelliteCommunicationController[] = {
    1,
    2,
    3,
    4
};

uint8_t PCIEncryptionController[] = {
    0,
    0x10,
    0x80
};

uint8_t PCISignalProcessingController[] = {
    0,
    1,
    0x10,
    0x20,
    0x80
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