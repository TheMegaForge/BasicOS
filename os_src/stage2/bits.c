#include "include/bits.h"


uint8_t bitClear8(uint8_t num,uint8_t bit){

    return num & ~((uint8_t)1 << bit);
}
uint16_t bitClear16(uint16_t num,uint8_t bit){

    return num & ~((uint16_t)1 << bit);
}
uint16_t bitClear32(uint16_t num,uint8_t bit){

    return num & ~((uint32_t)1 << bit);
}