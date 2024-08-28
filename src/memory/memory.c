//
// TODO: Rework ALL of this
//

#include "system.h"

static uint64_t allocated_memory = 0;

void* kmalloc(size_t size) {
    // jesus christ this is a bad way to allocate memory
    void* mem = (void*)((uint64_t)&end + allocated_memory);
    allocated_memory += size;
    return mem;
}

uint64_t get_used_memory(void) {
    return allocated_memory;
}
