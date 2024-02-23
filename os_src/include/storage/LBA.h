#pragma once
#include <stdint.h>
typedef uint32_t lba28;
typedef struct {
    uint32_t upper;
    uint16_t lower;
}LBA48_32BitMode;