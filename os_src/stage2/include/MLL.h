#pragma once
#include <stdint.h>
typedef struct{
    int layers;
    uint32_t usableMemory;
    uint32_t totalMemory;
    uint32_t acpiRecLayouts;
}LayoutInfo;
typedef enum{
    RT_FREE             = 1,
    RT_RES              = 2,
    RT_ACPI_RECLAIMABLE = 3,
    RT_ACPI_NVS         = 4
}RegionType;
typedef struct{
    uint32_t baddr_upper;
    uint32_t baddr_lower;
    uint32_t size_upper;
    uint32_t size_lower;
    RegionType rt;
}Region;
typedef struct{
    LayoutInfo info;
    Region regions[20];
    int FRegionsPos[6];
}Regions;
int getNumberOfLayouts();
void loadRegion(Region* reg,int pos);
void fetchRegions(Regions* reg);