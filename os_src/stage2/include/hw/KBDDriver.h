#pragma once
#include "../SwitchHandles.h"
#include <stdint.h>
//typedef void(*KBDPlug)(StageHandles* sh);
typedef int8_t char8_t;
typedef struct{
    const char tb[20];
    char(*await)(StageHandles* sh);
    char(*get)(StageHandles* sh);
    //int(*installListener)(StageHandles* sh,KBDPlug* plug);
    void(*fgets)(StageHandles* sh,char* location,uint8_t length);
    const uint8_t status;//read only
    const uint8_t tb_inc;
}KBDDriver;
char8_t await(StageHandles* sh);
char8_t get(StageHandles* sh);
void fgets(StageHandles* sh,char* location,uint8_t length);