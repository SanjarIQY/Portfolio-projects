#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "./source/h/my_string_lib.h"
#include "./source/h/structs.h"
#include "./source/h/sync_functions.h"
#include "./source/h/checking_functions.h"
#include <fcntl.h>

node_list* list = NULL;

void ls_option(int flag)
{
    node_list* l_list = list;
    if(flag == 0)
    {
        while(l_list)
        {
            printf("%d\n", l_list->id);
            l_list = l_list->next;
        }
    }
    else 
    {
        while(l_list)
        {
            printf("%d:", l_list->id);
            block_list* b_list = l_list->block;
            while(b_list)
            { 
                
                printf(" %d", b_list->id);
                if(block_length(l_list->block) > 1 && b_list->next != NULL)
                {
                    printf(",");
                }
                b_list = b_list->next;
            }
            
            l_list = l_list->next;
            printf("\n");
        }
    }
}

int rm_all_node()
{
    node_list* next = NULL;
    int flag = 0;
    while(list)
    {
        flag = 1;
        next = list->next;
        free_block_list(list->block);
        free(list);
        list = next;
    }

    if(flag == 1)
    {
        return 0;
    }
    else 
    {
        return 2;
    }
}

int rm_node(int id) 
{
    node_list* current = list;
    node_list* prev = NULL;
    int flag = 0;

    while(current) {
        if (current->id == id) 
        {
            flag = 1;
            if(prev == NULL) 
            {
                list = current->next;
                free_block_list(current->block);
                free(current);
                current = list;
            }
            else 
            {
                prev->next = current->next;
                free_block_list(current->block);
                free(current);
                current = prev->next;
            }
        } 
        else 
        {
            prev = current;
            current = current->next;
        }
    }
    if(flag == 0)
    {
        return 2;
    }
    else 
    {
        return 0;
    }
}

int rm_block(block_list** b_list, int id)
{
    block_list* current = *b_list;
    block_list* prev = NULL;
    int flag = 0;

    while(current) {
        if (current->id == id) {
            flag = 1;
            if(prev == NULL) {
                *b_list = current->next;
                free(current);
                current = *b_list;
            }
            else 
            {
                prev->next = current->next;
                free(current);
                current = prev->next;
            }
        } 
        else 
        {
            prev = current;
            current = current->next;
        }
    }
    if(flag == 0)
    {
        return 1;
    }
    else 
    {
        return 0;
    }
}

void search_node(char* block, char* node)
{
    int flag2 = 0;
    int flag = 0;
    node_list* l_list = list;
    while(l_list)
    {
        if (l_list->id == char_to_dec(node))
        {
            flag2 = 1;
            break;
        }
        l_list = l_list->next;
    }
    if(flag2 == 1)
    {
        flag = rm_block(&l_list->block,char_to_dec(block));
        rm_print(flag);
    }
    else 
    {
        rm_print(2);
    }
}

void rm_part(char** input)
{
    int flag = 0;
    if(!input[1])
    {
        printf("NOK: command not found\n");
    }
    else if(my_strcmp(input[1], "node") == 0)
    {
        if(!input[2])
        {
            write(2, "NOK: enter node id\n", 19);
            return;
        }
        else if(input[2][0] == '*')
        {
            flag = rm_all_node();
            rm_print(flag);
        }
        else if(input[2])
        {
            flag = rm_node(char_to_dec(input[2]));
            rm_print(flag);
        }
        else
        {
            printf("NOK: command not found\n");
        }
    }
    else if(my_strcmp(input[1], "block") == 0)
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
        else if(input[3][0] == '*')
        {
            node_list* l_list = list;
            int flag;
            while(l_list)
            {
                flag = rm_block(&l_list->block, char_to_dec(input[2]));
                l_list = l_list->next;
            }
            rm_print(flag);
        }
        else if(input[3])
        {
            search_node(input[2], input[3]);
        }
    }
}

void print_into_file(node_list* n_list)
{
    char* all_list = malloc(sizeof(char) * (size_of_list(list) + 1));
    fill_with_null(all_list, (size_of_list(list) + 1));
    int ind = 0;
    node_list* l_list = n_list;

    while(l_list)
    {
        char* num = dec_to_char((l_list->id));
        my_strcpy(&all_list[ind], num);
        ind += my_strlen(num);
        free(num);
        all_list[ind] = ' ';
        ind++;
        block_list* b_list = l_list->block;
        while(b_list)
        {
            char* b_num = dec_to_char(b_list->id);
            my_strcpy(&all_list[ind], b_num);
            ind += my_strlen(b_num);
            free(b_num);
            all_list[ind] = ' ';
            ind++;
            b_list = b_list->next;
        }
        if(l_list->next != NULL)
            all_list[ind] = '\n';
        ind++;
        l_list = l_list->next;
    }
    int fd = open("blockchain.txt", O_WRONLY | O_RDONLY);
    write(fd, all_list, my_strlen(all_list));
    free(all_list);
    close(fd);
}

void backingup_list(char* file_name)
{
    int fd = open(file_name, O_RDONLY);
    if(fd == -1)
    {
        creat(file_name, 000644);
    }
    close(fd);
    struct stat file_stat;
    stat(file_name, &file_stat);
    if(file_stat.st_size == 0)
    {
        printf("No Backup Found: Starting New Blockchain\n");
        return;
    }
    else
    {
        char* f_list = (char*)malloc(sizeof(char) * ((int)file_stat.st_size) + 1);
        fill_with_null(f_list, (int)file_stat.st_size + 1);
        int fd = open(file_name, O_RDONLY);
        read(fd, f_list, file_stat.st_size);
        close(fd);
        printf("Restoring From Backup\n");
        int i = 0;
        while(i < my_strlen(f_list))
        {
            if(f_list[i] >= 48 && f_list[i] <= 57)
            {
                char* num = malloc(sizeof(char) * 5);
                fill_with_null(num, 5);
                int ind = i;
                int num_ind = 0;
                int node_id;
                while(f_list[ind] >= 48 && f_list[ind] <= 57)
                {
                    num[num_ind++] = f_list[ind];
                    ind++;
                }
                if(i == 0 || f_list[i - 1] != ' ')
                {
                    node_id = char_to_dec(num);
                    add_node(node_id, &list);
                }
                else
                {
                    node_list* l_list = list;
                    while(l_list)
                    {
                        if(l_list->id == node_id)
                            break;
                        l_list = l_list->next;
                    }
                    add_block(char_to_dec(num),&l_list->block);
                }
                free(num);
                i = ind;
            }
            else
            {
                i++;
            }
        }
        free(f_list);
    }
    int ft = open(file_name, O_TRUNC);
    close(ft);
}

int give_path(char** input)
{
    if (my_strcmp(input[0], "add") == 0)
    {
        node_or_block(input, &list);
    }
    else if(my_strcmp(input[0], "rm") == 0)
    {
        rm_part(input);
    }
    else if (my_strcmp(input[0], "sync") == 0)
    {
        block_list* all = unique_blocks(list);
        synch(all, list);
        free_block_list(all);
    }
    else if (my_strcmp(input[0], "ls") == 0)
    {
        if(!input[1])
        {
            ls_option(0);
        }
        else if(my_strcmp(input[1], "-l") == 0)
        {
            ls_option(1);
        }
    }
    else if(my_strcmp(input[0], "quit") == 0)
    {
        printf("Backing up blockchain...\n");
        return 1;
    }
    else if(my_strcmp(input[0], "ping") == 0)
    {
        return 1;
    }
    else 
    {
        printf("NOK: command not found\n");
    }
    return 0;
}

void free_array(char** arr)
{
    for(int i = 0;arr[i] != NULL ; i++)
    {
        free(arr[i]);
    }
    free(arr);
}

int main()
{
    char* str;
    backingup_list("blockchain.txt");
    while(1)
    {
        prompt_identifier(list);
        str = my_scanf();
        split_gaps(str);
        char** str2 = split(str,' ');
        if(give_path(str2) == 1)
        {
            free_array(str2);
            free(str);
            break;
        }
        block_list* all = unique_blocks(list);
        check_for_sync(all, list);
        free(str);
        free_array(str2);
        free_block_list(all);
    } 
    print_into_file(list);
    free_node_list(list);
    return 0;
}
