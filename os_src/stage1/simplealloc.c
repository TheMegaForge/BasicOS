#include "../include/simplealloc.h"

void* allocate(struct SimpleAllocator* allocator,int size){
    void* snap = allocator->next;
    allocator->next+=size;
    return snap;
}
void deallocate(struct SimpleAllocator* allocator,int size){
    allocator->next-=size;
}

