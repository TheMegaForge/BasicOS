#pragma once
#include "stdint.h"
#include "stdbool.h"
__attribute__((packed)) struct NativeTalk{
    char* textAddress;
};
__attribute__((packed)) struct KernelTalk{
    struct PCIInformation{
        uint16_t harddrives;      
    };
};