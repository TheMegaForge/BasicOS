#pragma once
#include "../SwitchHandles.h"
#include <stdint.h>
//typedef void(*KBDPlug)( );
typedef int8_t char8_t;
typedef struct{
    uint8_t _char;
    bool active;
}KBDDriver;
char await();
void fgets(char* location,uint8_t length);
void fgets_tui(char* location,uint8_t  length,char** tb,enum _ColorCode cc);
void fgets_opi(char* location,uint8_t* cnt,char** tb,enum _ColorCode cc); // waits until enter key is pressed