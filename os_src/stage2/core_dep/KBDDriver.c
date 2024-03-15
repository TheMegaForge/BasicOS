#include "../include/hw/KBDDriver.h"
#include "../include/Keyboard.h"
#include "../include/bits.h"
#include "../../include/Driver.h"
extern StageHandles* _getHandles();
extern char* _drvGetTb(const char* drvD);
extern void _drvIncOrResetInc(const int* ci);
extern void _drvSetBufferFull(const uint8_t* status);
extern void _drvSetHold(const uint8_t* status);
extern void _drvSetReleased(const uint8_t* status);
bool isRelease(uint8_t c){
    return c >= 0x81;
}
extern KBDDriver* getKBD();
void __kbd__(Registers* regs){
    KBDDriver* kbd = getKBD();
    StageHandles* sh = _getHandles();
    uint8_t c = sh->inb_(KBD_DATA_PORT);
    if(kbd->active == true){
        kbd->_char = isRelease(c)*0x7C+(isRelease(c) == false)*c;
    }
}
char chars[] = {
    (char)0x1B,'1','2','3','4','5','6','7','8','9','0',
    '-','=',(char)0x8,(char)0x9,'q','w','e','r','t','y','u','i','o','p','[',']','\r',(char)17,
    'a','s','d','f','g','h','j','k','l',';','\'','`',(char)18,'\\','z','x','c','v','b','n','m',',',
    '.','/',(char)19,'*','!',' ',
};

char conv_c(uint8_t _c){
    return chars[_c - 1];
}
char await(){
    asm("cli");
    KBDDriver* kbd = getKBD();
    kbd->active = true;
    asm("sti");
    while(kbd->_char == 0x7C){}
    kbd->active = false;
    uint8_t back = kbd->_char;
    kbd->_char = 0x7C;
    return conv_c(back);
}
void fgets(char* location,uint8_t length){
    int inc = 0;
    for(int i = 0;i!=length;i++){
        location[inc] = await();
        inc++;
    }
}

void fgets_tui(char* location,uint8_t length,char** tb,enum _ColorCode cc){
    char* _tb = *tb;
    int inc = 0;
    for(int i = 0;i!=length;i++){
        char c = await();
        location[inc] = c;
        *_tb = c;
        *(_tb+1) = cc;
        _tb+=2;
    }
    *tb = _tb;
}

void fgets_opi(char* location,uint8_t* cnt,char** tb,enum _ColorCode cc){
    char* _tb = *tb;
    uint8_t inc = 0;
loop:
    char c = await();
    while(c != '\r'){
        if(c != 0x8){
            location[inc] = c;
            *_tb = c;
            *(_tb+1) = cc;
            inc++;
            _tb+=2;
            goto loop;
        }else{
            inc--;
            location[inc] = '\0';
            _tb-=2;
            *_tb = '\0';
            goto loop;
        }
    }
    *tb = _tb;
    *cnt = inc;
}