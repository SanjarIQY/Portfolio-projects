#ifndef MALLOC_STRUCT
#define MALLOC_STRUCT

typedef struct mem_alloc
{
    int size;
    int free;
    void* user_pointer;
    struct mem_alloc* next;
} block;

int hash_ident(int size);
void init();
void mmap_additional_mem();
void fill_with_null(void* mem_space, int size);
void* split_mem(int size, int c_flag);

#endif