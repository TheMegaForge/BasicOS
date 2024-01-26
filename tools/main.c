#include <stdint.h>
#include <stdio.h>
char* decimalChars = "0123456789";
void writeNumber(int num){
    do{
        uint8_t rem = num % 10;
        num = num/10;
        putc(decimalChars[rem],stdout);
    }while(num > 0);
}
int main(){
    writeNumber(100);
    return 0;
}