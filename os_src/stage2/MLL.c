#include "include/MLL.h"
#define BASE_MEM_MAP 0x9500
int getNumberOfLayouts(){
    return *(int*)0x9B00;
}


void loadRegion(Region* reg,int pos){
    int* mem_map = (int*)BASE_MEM_MAP;
    mem_map+=(pos*6);
    reg->baddr_lower = *mem_map;
    mem_map++;
    reg->baddr_upper = *mem_map;
    mem_map++;
    reg->size_lower  = *mem_map;
    mem_map++;
    reg->size_upper  = *mem_map;
    mem_map++;
    reg->rt         = (RegionType)*mem_map;
}


void fetchRegions(Regions* reg){
    reg->info.layers = getNumberOfLayouts();
    for(int i = 0;i<reg->info.layers;i++){
        loadRegion(&reg->regions[i],i);
    }
    reg->info.usableMemory = 0;
    reg->info.totalMemory  = 0;
    int inc = 0;
    for(int i = 0;i<reg->info.layers;i++){
        if(reg->regions[i].rt == RT_FREE){
            reg->info.usableMemory+=reg->regions[i].size_lower;
            reg->info.totalMemory+=reg->regions[i].size_lower;
            reg->FRegionsPos[inc] = i;
            inc++;
        }else if(reg->regions[i].rt == RT_RES){
            reg->info.totalMemory+=reg->regions[i].size_lower;
        }else if(reg->regions[i].rt == RT_ACPI_RECLAIMABLE){
            reg->info.acpiRecLayouts++;
        }else{
            
        }
    }
}