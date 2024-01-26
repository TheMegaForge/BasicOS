#include "../include/stdio.h"
#include "../include/memdefs.h"
#include "../include/string.h"
#include <stdbool.h>
#include "../include/i686/math.h"

extern __attribute__((cdecl)) const void* getAddressVarArg(void* bsp,uint8_t argPos);
typedef enum{
    PS_NORMAL    = 0,
    PS_LONG      = 1,
    PS_LONG_LONG = 2,
    PS_HALF      = 3,
    PS_HALF_HALF = 4,
    PS_UNSIGNED  = 5,
    PS_DIGIT     = 0xF0
}PrintState;
char* decimalNumbers = "0123456789";
char* hexNumbers     = "0123456789ABCDEF";

__cdecl char* putChar(char* memory,char c,uint8_t cc){
    *memory = c;
    *(memory+1) = cc;
    return (memory+=2);
}
__cdecl uint8_t puts(char** sl,char* str,enum _ColorCode cc){
    char* sll = *sl;
    int count = 0;
    while(*str != '\0'){
        sll = putChar(sll,*str,cc);
        str++;
        count++;
    }
    *sl = sll;
    return count;
}
__cdecl uint8_t newLine(char** sl,uint8_t writtenChars,enum _ColorCode cc){
    int neededChars = CHARS_PER_LINE-writtenChars;
    char* sll = *sl;
    while(neededChars != 0){
        sll = putChar(sll,'\0',cc);
        neededChars--;
    }
    *sl = sll;
    return CHARS_PER_LINE-writtenChars;
}
__cdecl uint8_t onLine(uint16_t line,char* data,enum _ColorCode cc){
    char* lineData = TEXT_BUFFER+((line*CHARS_PER_LINE)*2);
    int writtenChars = 0;
    while(*data != '\0'){
        lineData = putChar(lineData,*data,cc);
        data++;
        writtenChars++;
    }
    return writtenChars;
}

__cdecl uint8_t addressToLine(char* address){
    return (address-TEXT_BUFFER)/160;
}

__cdecl char*  lineToTextAddress(int line){
    return TEXT_BUFFER+((line--)*160);
}

__cdecl void kpanic(const char* data){
    char* textBuffer = (char*)TEXT_BUFFER+(CHARS_PER_LINE*2);
    setScreenColor(CC_RAW_RED);
    onLine(0,"[PANIC!]",CC_WHITE_RED);
    newLine(&textBuffer,puts(&textBuffer,data,CC_WHITE_RED),CC_RAW_RED);
    asm("cli");
    asm("hlt");
}

__cdecl void setScreenColor(enum _ColorCode cc){
    char* data = (char*)TEXT_BUFFER;
    for(int i = 0;i<LINES_PER_SCREEN*CHARS_PER_LINE;i++){
        *data = '\0';
        *(data++) = cc;
        data++;
    }
}
char numberToDecChar(uint32_t* num,uint32_t* rem){
    *rem = *num % 10;
    char* buffer = (char*)0;
    * num = *num / 10;
    return decimalNumbers[*rem];
}
uint8_t PutNumber(char* buffer,uint32_t num,bool hex){
    uint8_t written;
    do{
        uint32_t rem = 0;
        *buffer = numberToDecChar(&num,&rem);
        buffer--;
        written++;
    }while(num > 0);
    return written;
}
#define PRINTF_STATE_NORMAL         0
#define PRINTF_STATE_LENGTH         1
#define PRINTF_STATE_LENGTH_SHORT   2
#define PRINTF_STATE_LENGTH_LONG    3
#define PRINTF_STATE_SPEC           4

#define PRINTF_LENGTH_DEFAULT       0
#define PRINTF_LENGTH_SHORT_SHORT   1
#define PRINTF_LENGTH_SHORT         2
#define PRINTF_LENGTH_LONG          3
#define PRINTF_LENGTH_LONG_LONG     4
int* printf_number(int* argp, int length, bool sign, int radix);

void __attribute__((cdecl)) printf(const char* fmt, ...)
{
    
}
//TODO : LATER!