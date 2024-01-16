#include "../h/my_stdlib.h"

void my_free(void* mem_to_free)
{
    int i = 0;
    while (i < 7)
    {
        if (LIST[i] != NULL)
        {
            block* ptr = LIST[i];
            while (ptr != NULL)
            {
                if (ptr->user_pointer == mem_to_free)
                {
                    if(ptr->free == 1)
                    {
                        write(2, "free(): double free detected\n", 29);
                        return;
                    }
                    fill_with_null(ptr->user_pointer, ptr->size);
                    ptr->free = 1;
                }
                ptr = ptr->next;
            }
        }
        i++;
    }
}