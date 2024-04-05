
#include "../include/memory.h"

void error_exit(const char* message);

MemoryAllocationInfo* allocations = NULL;
int allocations_count = 0;
int allocations_capacity = 0;

void ensure_allocation_capacity(int min_capacity) {
    if (min_capacity > allocations_capacity) {
        int new_capacity = (allocations_capacity == 0) ? 1 : allocations_capacity * 2;
        MemoryAllocationInfo* new_allocations = realloc(allocations, new_capacity * sizeof(MemoryAllocationInfo));
        if (new_allocations == NULL) {
            error_exit("Erreur d'allocation mémoire lors de l'expansion du tableau d'enregistrements.\n");
        }
        allocations = new_allocations;
        allocations_capacity = new_capacity;
    }
}

void cleanup_memory_tracking() {
    for (int i = 0; i < allocations_count; i++) {
        if (allocations[i].ptr != NULL) {
            free(allocations[i].ptr);
            allocations[i].ptr = NULL; // Bonne pratique pour éviter les pointeurs pendouillants
        }
    }

    free(allocations);
    allocations = NULL;
    allocations_count = 0;
    allocations_capacity = 0;
}



void* custom_malloc(size_t size, char* description) 
{
    ensure_allocation_capacity(allocations_count + 1);
    void* ptr = malloc(size);
    if (ptr != NULL) {
        allocations[allocations_count].ptr = ptr;
        allocations[allocations_count].size = size;
        allocations[allocations_count].description = description;
        allocations_count++;
    } else {
        error_exit("malloc a échoué dans custom_malloc.\n");
    }

    return ptr;
}

void custom_free(void* ptr) {
    for (int i = 0; i < allocations_count; i++) {
        if (allocations[i].ptr == ptr) {
            allocations[i].ptr = NULL;
            free(ptr);
            return;
        }
    }
}

void print_memory_usage() {
    size_t total_memory = 0;
    // printf("Détail des allocations mémoire:\n");
    for (int i = 0; i < allocations_count; i++) {
        if (allocations[i].ptr != NULL) {
            //printf("Alloc: %s, Taille: %zu octets\n", allocations[i].description, allocations[i].size);
            total_memory += allocations[i].size;
        }
    }
    //printf("Mémoire totale allouée: %zu octets\n", total_memory);
}

const int max_allocations = 5000;
int allocation_counter = 0;

static const int print_threshold = max_allocations / 10;

int print_counter = 0;
const int total_prints = 10;

void* allocate_and_report(size_t size, char* description) {
    void *ptr = custom_malloc(size, description);
    if (!ptr) {
        error_exit("Erreur d'allocation mémoire\n");
    }

    allocation_counter++;

    if (print_counter < total_prints && (allocation_counter >= (print_threshold * (print_counter + 1)))) 
    {
        //printf("Description : %s\n", description);
        print_memory_usage();
        print_counter++;
    }

    return ptr;
}
