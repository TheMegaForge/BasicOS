#include "../include/string.h"
int strlen(char* data){
    int len = 0;
    int counter = MAX_STRING_LENGTH;
    while(*data != '\0' && counter != 0){
        counter--;
        len++;
    }
    return len;
}
void memcpy(void* restrict dest,void* restrict src,int size){
    char* ptr = src;
    char* _dest  = dest;
    for(int i=0;i<size;i++){
        *_dest = *ptr;
        _dest++;
        ptr++;
    }
}