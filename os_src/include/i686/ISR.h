#pragma once
#include "../stdint.h"
typedef struct {
    uint32_t ds;
    uint32_t edi,esi,ebp,kernel_esp,ebx,edx,ecx,eax;
    uint32_t interrupt,error;
    uint32_t eip,cs,eflags,esp,ss;
}__attribute__((packed)) Registers;

