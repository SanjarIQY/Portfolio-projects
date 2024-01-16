#include "../h/structs.h"
#include "../h/checking_functions.h"
#include "../h/my_string_lib.h"
#include <stdlib.h>
#include <stdio.h>

block_list* unique_blocks(node_list* n_list)
{
    node_list* loop = n_list;
    block_list* all = NULL;
    while(loop)
    {
        block_list* b_loop = loop->block;
        while(b_loop)
        {
            if(check_for_id(all, b_loop->id) == 0)
            {
                add_block(b_loop->id, &all);
            }
            b_loop = b_loop->next;
        }
        loop = loop->next;
    }    
    return all;
}


void synch(block_list* all, node_list* n_list)
{
    node_list*l_list = n_list;
    int flag;

    while(l_list)
    {
        int* lacking_numbers = (int*)calloc(sizeof(int) , (block_length(all)) + 1);
        int index = 0;
        block_list* b_all = all;
        while(b_all)
        {
            block_list* b_block = l_list->block;
            flag = 0;
            while(b_block)
            {
                if(b_block->id == b_all->id)
                {
                    flag = 1;
                }
                b_block = b_block->next;
            }
            if(flag == 0)
            {
                lacking_numbers[index] = b_all->id;
                index++;
            }
            b_all = b_all->next;
        }
        int i = 0;
        while(lacking_numbers[i] != 0)
        {
            add_block(lacking_numbers[i], &l_list->block);
            i++;
        }
        free(lacking_numbers);
        free_block_list(b_all);
        l_list =l_list->next;
    }
    printf("OK\n");
}