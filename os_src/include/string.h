#pragma once
#define MAX_STRING_LENGTH 2048
#include "stdint.h"
int strlen(char* data);
void memcpy(void* restrict dest,void* restrict src,int size);
extern __attribute__((cdecl)) int countStructuresInMemorySpace(void* end,void* beg,unsigned char structSize);
extern __attribute__((cdecl)) uint8_t extractByte(uint32_t number,uint32_t mask,uint8_t rightShift);