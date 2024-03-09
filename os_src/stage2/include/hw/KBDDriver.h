#pragma once
#include "../SwitchHandles.h"
#include <stdint.h>
//typedef void(*KBDPlug)(StageHandles* sh);
typedef int8_t char8_t;
typedef struct{
    uint8_t rep[100];
    uint8_t buf[100];
    bool held;
    bool output;
    uint8_t curr;
    uint8_t lread;
    uint8_t read;
    bool active;
}KBDDriver;
char await(StageHandles* sh);
void fgets(StageHandles* sh,char* location,uint8_t length);
void fgets_tui(StageHandles* sh,char* location,uint8_t  length,char** tb,enum _ColorCode cc);
void fgets_opi(StageHandles* sh,char* location,uint8_t* cnt,char** tb,enum _ColorCode cc); // waits until enter key is pressed