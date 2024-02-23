#pragma once
#include "AHCIStructs.h"
#include <stdbool.h>
#include "../PCI.h"
/*
    -- INFORMATION --
    Handles SATA Devices
        

*/
bool isACHICapable(PCIBus* bus,_PCIDeviceDescriptor* Outdescriptor);
//ABAR = AHCI Base Memory Register
bool readABAR(_PCIDeviceDescriptor* descriptor);