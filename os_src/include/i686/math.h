#pragma once
#include "../stdint.h"
extern __attribute__((cdecl)) uint8_t LeftRoll8(uint8_t num,uint8_t rolls);
extern __attribute__((cdecl)) uint16_t LeftRoll16(uint16_t num,uint8_t rolls);
extern __attribute__((cdecl)) uint32_t LeftRoll32(uint32_t num,uint8_t rolls);

extern __attribute__((cdecl)) uint8_t RightRoll8(uint8_t num,uint8_t rolls);
extern __attribute__((cdecl)) uint16_t RightRoll16(uint16_t num,uint8_t rolls);
extern __attribute__((cdecl)) uint32_t RightRoll32(uint32_t num,uint8_t rolls);

int getDigitsInNumber(int number);
int abs(int num);