#ifndef ARCH_H_
#define ARCH_H_

#define IS_PROT_MODE 1
#define IS_LONG_MODE 0
extern __attribute__((cdecl)) void kpanic(const char* msg);
void KpanicOnProtMode(){
    if(IS_PROT_MODE == 1)
        kpanic("PROTECTED MODE IN LONG MODE AREA!");
    else
        return;
}
void KpanicOnLongMode(){
    if(IS_LONG_MODE == 1)
        kpanic("LONG MODE IN PROTECTED MODE ARE!");
    else
        return;
}
#endif