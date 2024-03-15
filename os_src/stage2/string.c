#include "include/string.h"


int strncmp(char* str,char* cmpTo,int len){
    int col = 0;
    for(int i = 0;i<len;i++){
        col+=str[i];
        col-=cmpTo[i];
    }
    return col;
}