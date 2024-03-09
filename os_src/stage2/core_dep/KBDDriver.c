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
    bool isRel = isRelease(c);
    bool isSame = (kbd->buf[kbd->curr] == c) || kbd->buf[kbd->curr] == 0xFF;
    kbd->held = (isRel == false);
    //TODO: TEST!
    if(!isRel  && kbd->curr < 100 && kbd->active == true){
        kbd->output = true;
        int w;
        //handle if diffrent
        uint8_t _buc = kbd->buf[kbd->curr];
        uint8_t __c = kbd->curr;
        kbd->curr += ((isSame == false));
        kbd->buf[kbd->curr] = (((__c == kbd->curr)== false) || kbd->buf[kbd->curr] == 0xFF)*c+((__c == kbd->curr) && kbd->buf[kbd->curr] != 0xFF )*_buc;//works
        kbd->rep[kbd->curr] +=(__c == kbd->curr);
        kbd->rep[kbd->curr] = ((__c == kbd->curr)*kbd->rep[kbd->curr])+((__c == kbd->curr) == false);
        //increment when not diffrent
        kbd->read++;
        //w = sh->printf(sh->_tb,"hld=%bb",CC_WHITE_BLUE,kbd->held);
        //sh->_tb+=(w*2);
        return;
    }
    kbd->curr -=100*(isRel == false);
    kbd->held = false;
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
char await(StageHandles* sh){
    asm("cli");
    KBDDriver* kbd = getKBD();
    kbd->lread = kbd->curr;
    kbd->active = true;
    kbd->held = true;
    asm("sti");
loop:
    while(!kbd->output){}
    if(kbd->held){
        goto loop;
    }
    kbd->lread = kbd->curr;
    uint8_t c = kbd->buf[kbd->lread];
    kbd->read = 0;
    kbd->held = false;
    kbd->output = false;
    kbd->active = false;
    return conv_c(c);
}
void fgets(StageHandles* sh,char* location,uint8_t length){
    int inc = 0;
    for(int i = 0;i!=length;i++){
        location[inc] = await(sh);
        inc++;
    }
}

void fgets_tui(StageHandles* sh,char* location,uint8_t length,char** tb,enum _ColorCode cc){
    char* _tb = *tb;
    int inc = 0;
    for(int i = 0;i!=length;i++){
        char c = await(sh);
        location[inc] = c;
        *_tb = c;
        *(_tb+1) = cc;
        _tb+=2;
    }
    *tb = _tb;
}

void fgets_opi(StageHandles* sh,char* location,uint8_t* cnt,char** tb,enum _ColorCode cc){
    char* _tb = *tb;
    uint8_t inc = 0;
loop:
    char c = await(sh);
    while(c != '\r'){
        location[inc] = c;
        *_tb = c;
        *(_tb+1) = cc;
        inc++;
        _tb+=2;
        goto loop;
    }
    *tb = _tb;
    *cnt = inc;
}