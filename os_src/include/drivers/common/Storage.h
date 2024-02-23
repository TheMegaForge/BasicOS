#pragma once
#include <stdint.h>
#define CMN_STORAGE_ID 1
typedef enum{
    CSE_SUCCESS             = 0,
    CSE_INVALID_SECTOR      = 1,
    CSE_OUT_OF_DISK         = 2,
    CSE_PROTECTED           = 3,
    CSE_WRONG_TYPE          = 4,
    CSE_ON_DELETED_CLUSTERS = 5 | 0x8000,
    CSE_TO_LARGE_SECTORS    = 6,
    CSE_INVALID_PTR         = 7,
    CSE_INVALID_READ        = 8,
    CSE_TO_TINY_SECTORS     = 9,
    CSE_EXTRA_RETURN_MASK  = 0x8000
}CMNStorageError;
typedef enum{
    CCT_512   = 1,
    CCT_1024  = 2,
    CCT_2024  = 4,
    CCT_4048  = 8,
    CCT_12144 = 16
}CMNStorageClusterType;
typedef enum {
    DRV_ATA                     = 0,
    DRV_SATA                    = 1,
    DRV_NVMe                    = 2,
    DRV_NVMe2                   = 3,
    DRV_NEEDS_EXTRA_STRUCT_MASK = 0x8100,
    DRV_UNSUPPORTED_COMMON      = 0x8110,
}CMNStorageHeaderType;
typedef struct {
    int32_t upper[32];
    int16_t middle[16];
    int8_t low[16];
}CMNStorageReturnData;
typedef struct {
    CMNStorageHeaderType ht;
    CMNStorageError(*read)(void* extraStruct,CMNStorageClusterType ct,
                            uint32_t readCount,uint32_t lba,
                           CMNStorageReturnData* ret,CMNStorageReturnData* extraRet,
                           uint16_t* buffer);
    CMNStorageError(*write)(void* extraStruct,CMNStorageClusterType ct,
                            uint32_t writeCount,uint32_t lba,
                            CMNStorageReturnData* ret,CMNStorageReturnData* extraRet,
                            uint16_t* buffer);
}StorageCommon;