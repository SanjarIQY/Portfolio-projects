#include "../h/structs.h"
#include "../h/my_string_lib.h"
#include "../h/sync_functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int check_for_id(block_list* all, int id)
{
    while(all)
    {   
        if(all->id == id)
        {
            return 1;
        }
        all = all->next;
    }
    return 0;
}

int check_for_sync(block_list* all, node_list* n_list)
{
    node_list* l_list = n_list;
    int counter = 0;

    while(l_list)
    {
        counter = 0;
        block_list* b_all = all;
        while(b_all)
        {
            block_list* b_block = l_list->block;
            while(b_block)
            {
                if(b_block->id == b_all->id)
                {
                    counter++;
                }
                b_block = b_block->next;
            }
            b_all = b_all->next;
        }
        if(counter != block_length(all))
        {
            return 0;
        }
        l_list = l_list->next;
    }
    return 1;
}

void prompt_identifier(node_list* n_list)
{
    block_list* all = unique_blocks(n_list);
    char* prompt = malloc(sizeof(char)*4);
    fill_with_null(prompt, 4);
    if(check_for_sync(all, n_list) == 1)
    {
        prompt[0] = 's';
    }
    else{
        prompt[0] = '-';
    }
    if(node_length(n_list) == 0)
    {
        my_strcpy(&prompt[1],"0");
    }
    else 
    {
        char* num = dec_to_char(node_length(n_list));
        my_strcpy(&prompt[1],num);
        free(num);
    }
    free_block_list(all);
    printf("[%s]>", prompt);
    fflush(stdout);
    free(prompt);
}


void path(int id, char* node_id, node_list* n_list)
{
    if(node_id[0] == '*')
    {
        node_list* loop = n_list;
        while(loop)
        {
            if(check_for_dublicates_b(id,loop) == 1)
            {
                write(2, "NOK: this block already exists\n",31);
                loop = loop->next;
            }
            else
            {
                add_block(id, &loop->block);
                loop = loop->next;
            }
        }
        printf("OK\n");
    }
    else {
        
        node_list* loop = n_list;
        while(loop)
        {
            if(loop->id == char_to_dec(node_id))
                break;
            loop = loop->next;
        }
        if(check_for_dublicates_b(id, loop) == 1)
        {
            write(2, "NOK: this block already exists\n",31);
            return;
        }
        add_block(id, &loop->block);
        printf("OK\n");
    }
}

void node_or_block(char** input, node_list** n_list)
{
    if(!input[1])
    {
        printf("NOK: command not found\n");
    }
    else if (my_strcmp(input[1], "node") == 0)
    {
        if(!(input[2]))
        {
            write(2, "NOK: enter node id\n", 19);
            return;
        }
        else if(check_for_dublicates_n(char_to_dec(input[2]), *n_list) == 1)
        {
            write(2, "NOK: this node already exists\n", 30);
            return;
        }
        add_node(char_to_dec(input[2]), n_list);
        printf("OK\n");
    }
    else if (my_strcmp(input[1], "block") == 0)
    {
        if(!(input[2]))
        {
            write(2, "NOK: enter block id\n", 20);
            return;
        }
        else if(!(input[3]))
        {
            write(2, "NOK: enter node id\n", 19);
            return;
        }
        else if(input[3][0] != '*' && check_for_dublicates_n(char_to_dec(input[3]), *n_list) == 0)
        {
            write(2, "NOK: node doesn't exist\n", 24);
            return;
        }
        path(char_to_dec(input[2]), input[3], *n_list);
    }
}
