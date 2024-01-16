#include "../h/my_stdlib.h"

void init()
{
    big_chunk_mem = mmap(NULL, AVAILABLE_MEM, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    chunk_to_free = big_chunk_mem;
    ALLOCATED_MEM += AVAILABLE_MEM;
}

int hash_ident(int size)
{
    if (size >= 0 && size <= 10)
    {
        return 0;
    }
    else if (size >= 11 && size <= 100)
    {
        return 1;
    }
    else if (size >= 101 && size <= 500)
    {
        return 2;
    }
    else if (size >= 501 && size <= 1500)
    {
        return 3;
    }
    else if (size >= 1501 && size <= 2500)
    {
        return 4;
    }else if(size >= 2501 && size <= 4000)
    {
        return 5;
    }
    return 6;
}

void fill_with_null(void* mem_space, int size)
{
    char* converted = (char*)mem_space;
    for (int i = 0; i < size ; i++)
    {
        *converted = '\0';
        converted++;
    }
}

void mmap_additional_mem()
{
    void* temp =  mmap(NULL, AVAILABLE_MEM + ALLOCATED_MEM, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    memcpy(temp, big_chunk_mem, ALLOCATED_MEM);
    munmap(big_chunk_mem, ALLOCATED_MEM);
    ALLOCATED_MEM += AVAILABLE_MEM;
    big_chunk_mem = temp;
    chunk_to_free = big_chunk_mem;
}

void* split_mem(int size, int flag)
{
    if ((ALLOCATED_MEM - mem_size) < size)
    {
        mmap_additional_mem();
    }
    int hash_index = hash_ident(size);
    if (LIST[hash_index] == NULL)
    {
        LIST[hash_index] = (block*)big_chunk_mem;
        LIST[hash_index]->user_pointer = (void*)LIST[hash_index] + sizeof(block);
        big_chunk_mem += sizeof(block) + size;
        LIST[hash_index]->size = size;
        LIST[hash_index]->free = 0;
        LIST[hash_index]->next = NULL;
        if (flag == 1)
        {
            fill_with_null(LIST[hash_index]->user_pointer, size);
        }
        mem_size += LIST[hash_index]->size;
        return LIST[hash_index]->user_pointer;
    }
    else 
    {
        block* ptr = LIST[hash_index];
        while (ptr->next != NULL)
        {
           ptr = ptr->next; 
        }
        ptr->next = (block*)big_chunk_mem;
        ptr->next->user_pointer = (void*)ptr->next + sizeof(block);
        big_chunk_mem += sizeof(block) + size;
        ptr->next->size = size;
        ptr->next->free = 0;
        if (flag == 1)
        {
            fill_with_null(ptr->next->user_pointer, size);
        }
        ptr->next->next = NULL;
        mem_size += ptr->next->size;
        return ptr->next->user_pointer;
    }
}

