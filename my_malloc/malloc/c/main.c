#include "../h/my_stdlib.h"

int AVAILABLE_MEM = 4092;
int ALLOCATED_MEM = 0;
block* LIST[7];
void* big_chunk_mem = NULL;
void* chunk_to_free;
int mem_size = 0;

int main()
{
    if (chunk_to_free != NULL)
    {
        munmap(chunk_to_free, ALLOCATED_MEM);
    }
}