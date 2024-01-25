#pragma once
#include "stdint.h"

__attribute__((packed)) struct SimpleAllocator{
    void* base;
    void* limit;
    void* next;
};
void* allocate(struct SimpleAllocator* allocator,int size);
void deallocate(struct SimpleAllocator* allocator,int size);
