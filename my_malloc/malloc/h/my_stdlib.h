#ifndef LIBRARIES_AND_VARIABLES
#define LIBRARIES_AND_VARIABLES

#include <stdio.h>
#include <alloca.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>

#include "./struct.h"

extern int mem_size;
extern int ALLOCATED_MEM;
extern int AVAILABLE_MEM; 
extern void* chunk_to_free;
extern void* big_chunk_mem;
extern block* LIST[];

#endif

#ifndef MY_MALLOC
#define MY_MALLOC

void* my_malloc(size_t size);

#endif

#ifndef MY_CALLOC
#define MY_CALLOC

void* my_calloc(size_t numb, size_t type);

#endif

#ifndef MY_REALLOC
#define MY_REALLOC

void* my_realloc(void *ptr, size_t size);

#endif

#ifndef MY_FREE
#define MY_FREE

void my_free(void* allocated_mem);

#endif

