#include "../include/stdio.h"
#include "../include/memdefs.h"
#include "../include/string.h"
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
/*__cdecl void* copyDescriptorOutput(void* storeAddress,struct DescriptorOutput* new,struct DescriptorOutput* old){
    
}*/
/*__cdecl struct DescriptorOutput* putDescriptorMessage(int line,struct TextDescriptor* descriptor){
    char* text = descriptor->text;
    char* addr = lineToTextAddress(line);
    struct DescriptorOutput* output = (struct DescriptorOutput*)TEXT_DESC_OUTPUT;
    output->count       = descriptor->descSize;
    output->colors      = TEXT_DESC_OUTPUT+sizeof(struct DescriptorOutput);
    output->desc        = output->colors+(sizeof(uint8_t)*descriptor->descSize);
    output->textPtrs    = output->desc+(sizeof(uint16_t)*descriptor->descSize);

    memcpy(output->colors,descriptor->descriptorColors,descriptor->descSize);
    memcpy(output->desc,descriptor->desc,sizeof(uint16_t)*descriptor->descSize);

    for(uint16_t i = 0;i<descriptor->descSize;i++){
        uint16_t CDL = descriptor->desc[i];
        uint8_t C_cc = descriptor->descriptorColors[i];
        while(CDL != 0){
            if(*text == ' '){
                addr = putChar(addr,' ',descriptor->whitespaceColor);
                output->whitespaces++;
                text++;
            }else{
                addr = putChar(addr,*text,C_cc);
                text++;
            }
        }
    }
    return output;
}*/
