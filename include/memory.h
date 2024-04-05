#ifndef MEMORY_H
#define MEMORY_H

#include <stdio.h>
#include <stdlib.h>

extern int allocation_counter;

typedef struct MemoryAllocationInfo {
    void* ptr;
    size_t size;
    char* description;
} MemoryAllocationInfo;

void* custom_malloc(size_t size, char* description);
void custom_free(void* ptr);
void print_memory_usage();
void* allocate_and_report(size_t size, char* description);
void cleanup_memory_tracking();
#endif


