#pragma once
#include "../stdint.h"
__attribute__((cdecl)) void outb_(unsigned short int port,uint8_t data);
__attribute__((cdecl)) void outs_(unsigned short int port,uint16_t data);
__attribute__((cdecl)) void outi_(unsigned short int port,uint32_t data);
__attribute__((cdecl)) uint8_t inb_(uint16_t port);
__attribute__((cdecl)) uint16_t ins_(uint16_t port);
__attribute__((cdecl)) uint32_t ini_(uint16_t port);