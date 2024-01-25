#pragma once
#include "../stdint.h"
#include "../stdbool.h"
#define FLAG_SET(x,flag) x|=flag
#define FLAG_UNSET(x,flag) x &= ~flag
extern __attribute__((cdecl)) uint16_t extractWordFromDWord(uint32_t dword,bool isUpper);
extern __attribute__((cdecl)) uint8_t extractByteFromWord(uint16_t word,bool isUpper);