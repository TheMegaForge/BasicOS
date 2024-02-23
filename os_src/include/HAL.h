#pragma once

#include "PCI.h"
#include "storage/IDE.h"
#include "storage/ATA.h"
void HAL_Initilize(ATAController* controller,PCIBus* pciBus,IDEController* ide,StorageCommon* storage);
