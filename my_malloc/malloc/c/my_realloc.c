#include "../h/my_stdlib.h"

void* my_realloc(void* allocated_mem, size_t size)
{
    int i = 0;
    while (i < 7)
    {
        if (LIST[i] != NULL)
        {
            block* ptr = LIST[i];
            while (ptr)
            {
                if (ptr->user_pointer == allocated_mem)
                {
                    void* temp = my_malloc(size);
                    memcpy(temp, allocated_mem, ptr->size);
                    my_free(ptr->user_pointer);
                    return temp;
                }
                ptr = ptr->next;
            }
        }
        i++;
    }
    return NULL;
}
