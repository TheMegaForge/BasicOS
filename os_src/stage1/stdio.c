#include "../include/stdio.h"
#include "../include/memdefs.h"
#include "../include/string.h"
#include <stdbool.h>
#include "../include/i686/math.h"
char* decimalNumbers = "0123456789";
char* hexNumbers     = "0123456789ABCDEF";
__cdecl char* putc(char* memory,char c,uint8_t cc){
    *memory = c;
    *(memory+1) = cc;
    return (memory+=2);
}
__cdecl uint8_t puts(char** sl,char* str,enum _ColorCode cc){
    char* sll = *sl;
    int count = 0;
    while(*str != '\0'){
        sll = putc(sll,*str,cc);
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
        sll = putc(sll,'\0',cc);
        neededChars--;
    }
    *sl = sll;
    return CHARS_PER_LINE-writtenChars;
}
__cdecl uint8_t onLine(uint16_t line,char* data,enum _ColorCode cc){
    char* lineData = TEXT_BUFFER+((line*CHARS_PER_LINE)*2);
    int writtenChars = 0;
    while(*data != '\0'){
        lineData = putc(lineData,*data,cc);
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
    newLine(&textBuffer,puts(&textBuffer,(char*)data,CC_WHITE_RED),CC_RAW_RED);
    asm("cli");
    asm("hlt");
}

__cdecl void setScreenColor(enum _ColorCode cc){
    char* data = (char*)TEXT_BUFFER;
    for(int i = 0;i<LINES_PER_SCREEN*CHARS_PER_LINE;i++){
        data = putc(data,'\0',cc);
    }
}
char numberToDecChar(uint32_t* num,uint32_t* rem){
    *rem = *num % 10;
    char* buffer = (char*)0;
    * num = *num / 10;
    return decimalNumbers[*rem];
}
char* putUNum(char* textBuffer,uint32_t num,enum _ColorCode cc){
    char buffer[20];
    int i = 0;
    do{
        uint8_t rem = num % 10;
        num = num/10;
        buffer[i] = decimalNumbers[rem];
        i++;
    }while(num > 0);
    int j = i-1;
    while(j !=-1){
        textBuffer = putc(textBuffer,buffer[j],cc);
        j--;
    }
    return textBuffer;
}
char* putNum(char* textBuffer,int32_t num,enum _ColorCode cc){
    char buffer[20];
    int i = 0;
    bool isNegativ = num < 0;
    do{
        uint8_t rem = num % 10;
        num = num/10;
        buffer[i] = decimalNumbers[rem];
        i++;
    }while(num > 0);
    int j = i-1;
    if(isNegativ){
        textBuffer = putc(textBuffer,'-',cc);
    }
    while(j !=-1){
        textBuffer = putc(textBuffer,buffer[j],cc);
        j--;
    }

    return textBuffer;
}
char* putHexNum(char* tb,uint32_t hex,enum _ColorCode cc){
    char buffer[20];
    int i = 0;
    do{
        uint8_t rem = hex % 16;
        hex = hex/16;
        buffer[i] = hexNumbers[rem];
        i++;
    }while(hex > 0);
    int j = i-1;
    tb = putc(tb,'0',cc);
    tb = putc(tb,'x',cc);
    while(j !=-1){
        tb = putc(tb,buffer[j],cc);
        j--;
    }

    return tb;
}
char* parsePrint(char* tb,char** str,enum _ColorCode cc,int** argp,int* written){
    char* _str = *str;
    switch(*_str){
        case 'c':{
            _str++;
            char c = (char)(uint32_t)**argp;
            tb = putc(tb,c,cc);
            int* _argp = *argp;
            _argp++;
            *argp = _argp;
            *written = 1;
        }break;
        case 'd':{
            _str++;
            int32_t num = (int32_t)**argp;
            char* tbSnap = tb;
            tb = putNum(tb,num,cc);
            *written = (tb-tbSnap)/2;
            int* _argp = *argp;
            _argp++;
            *argp = _argp;
        }break;
        case 's':{
            _str++;
            char* tbSnap = tb;
            char* _addr = (char*)**argp;
            int* _argp = *argp;
            _argp++;
            *argp = _argp;
            *written = (int)puts(&tb,_addr,cc);
        }break;
    ptr:
        case 'p':{
            _str++;
            uint32_t hex = (uint32_t)**argp;
            int* _argp = *argp;
            _argp++;
            *argp = _argp;
            char* tbSnap = tb;
            tb = putHexNum(tb,hex,cc);
            *written = (tb-tbSnap)/2;
        };break;
        case 'x':{
            goto ptr;
        }
    }
    *str = _str;
    return tb;
};
int printf(char* textBuffer,char* str,enum _ColorCode cc,...){
    char* tb = textBuffer;
    int written = 0;
    int* argp = (int*)&cc;
    argp++;
    while(*str != '\0'){
        if(*str != '%' && *str != '\0'){
            tb = putc(tb,*str,cc);
            str++;
            written++;
        }else{
            str++;
            int wr = 0;
            tb = parsePrint(tb,&str,cc,&argp,&wr);
            written+=wr;
        }
    }
    return written;
}
