#include "../h/structs.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int check_for_dublicates_b(int id, node_list* n_list)
{
    block_list* b__list = n_list->block;
    while(b__list)
    {
        if(b__list->id == id)
        {
            return 1;
        }
        b__list = b__list->next;
    }
    return 0;
}

int check_for_dublicates_n(int id, node_list* n_list)
{
    node_list* l_list = n_list;
    while(l_list)
    {
        if(l_list->id == id)
        {
            return 1;
        }   
        l_list = l_list->next;
    }
    return 0;
}

void add_node(int id, node_list** list)
{
    node_list* current = (node_list*)malloc(sizeof(node_list));
    current->id = id;
    current->next = NULL;
    current->block = NULL;

    if(*list == NULL)
    {
        *list = current;
    }
    else
    {
        node_list* loop = *list;
        while(loop->next != NULL)
        {
            loop = loop->next;
        }
        loop->next = current;
    }
}

void add_block(int id, block_list** block)
{
    block_list* current = (block_list*)malloc(sizeof(block_list));
    current->id = id;
    current->next = NULL;

    if(*block == NULL)
        *block = current;
    else
    {
        block_list* loop = *block;
        while(loop->next)
        {
            loop = loop->next;
        }
        loop->next = current;
    }
}

int block_length(block_list* b_list)
{
    int length = 0;
    block_list* b__list = b_list;
    while(b__list)
    {
        length++;
        b__list = b__list->next;
    }
    return length;
}

int node_length(node_list* n_list)
{
    node_list* l_list = n_list;
    int length = 0;
    while(l_list)
    {
        length++;
        l_list = l_list->next;
    }
    return length;
}

int size_of_list(node_list* n_list)
{
    node_list* l_list = n_list;
    int counter = 0;
    while(l_list)
    {
        block_list* b_list = l_list->block;
        while(b_list)
        {
            counter++;
            b_list = b_list->next;
        }
        l_list = l_list->next;
        counter++;
    }
    return counter * 3;
}

void rm_print(int flag)
{
    if(flag == 1)
    {
        write(2, "NOK: block doesn't exist\n", 25);
        return;
    }
    else if(flag == 2)
    {
        write(2, "NOK: node doesn't exist\n", 24);
        return;
    }
    else
    {
        printf("OK\n");
    }
}

void free_block_list(block_list* l_list)
{
    block_list* b_list = l_list;
    block_list* b_next;

    while(b_list != NULL)
    {
        b_next = b_list->next;
        free(b_list);
        b_list = b_next;
    }
}

void free_node_list(node_list* n_list)
{
    node_list* l_list = n_list;
    node_list* next_list;

    while(l_list != NULL)
    {
        free_block_list(l_list->block);
        next_list = l_list->next;
        free(l_list);
        l_list = next_list;
    }
}

