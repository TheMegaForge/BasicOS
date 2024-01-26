#pragma once
#include <stdint.h>
#include <stdbool.h>
#include "stddef.h"
#define CHARS_PER_LINE 80
#define LINES_PER_SCREEN 25
#define LAST_SCREEN_LINE 23
#define TEXT_BUFFER (char*)0xb8000
enum _ColorCode{
    CC_RAW_BLUE = 0x11,
    CC_RAW_RED = 0x44,
    CC_WHITE_BLUE = 0x1F,
    CC_BLACK_BLUE = 0x01,
    CC_GREEN_BLUE = 0x21,
    CC_YELLOW_BLUE = 0xE1,
    CC_WHITE_RED   = 0xF4
};
__attribute__((packed))  struct DescriptorOutput{
    uint16_t count;
    uint16_t whitespaces;
    char** textPtrs;
    uint16_t* desc; //length of the 'n' strings
    uint8_t* colors;
};
__attribute__((packed))  struct TextDescriptor{
    char* text;
    uint16_t descSize;
    uint16_t* desc;
    uint8_t* descriptorColors;
    uint8_t whitespaceColor;
};

extern __attribute__((cdecl)) uint8_t getUByteVarArg(void* bsp,uint8_t argPos);
extern __attribute__((cdecl)) uint16_t getUShortVarArg(void* bsp,uint8_t argPos);
extern __attribute__((cdecl)) uint32_t getUIntVarArg(void* bsp,uint8_t argPos);

extern __attribute__((cdecl)) int8_t getByteVarArg(void* bsp,uint8_t argPos);
extern __attribute__((cdecl)) int16_t getShortVarArg(void* bsp,uint8_t argPos);
extern __attribute__((cdecl)) int32_t getIntVarArg(void* bsp,uint8_t argPos);



char numberToDecChar(uint32_t* num,uint32_t* rem);
uint8_t PutNumber(char* buffer,uint32_t num,bool hex);
__cdecl char* putChar(char* memory,char c,uint8_t cc);
__cdecl uint8_t puts(char** sl,char* str,enum _ColorCode cc);
int printf(char* textBuffer,char* str,enum _ColorCode cc,...);
__cdecl uint8_t newLine(char** sl,uint8_t writtenChars,enum _ColorCode cc);
__cdecl uint8_t onLine(uint16_t line,char* data,enum _ColorCode cc);
__cdecl uint8_t addressToLine(char* address);
__cdecl char*   lineToTextAddress(int line);
__cdecl void setScreenColor(enum _ColorCode cc);
__cdecl void kpanic(const char* data);