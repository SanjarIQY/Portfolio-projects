#include "../h/data_process.h"

void add_list(b_block** header, char* line, int line_length)
{
    b_block* current = (b_block*)malloc(sizeof(b_block));
    current->line = calloc(sizeof(char), line_length + 1);
    my_strcpy(current->line, line);
    current->next = NULL;

    if (*header == NULL)
    {
        *header = current;
    }
    else
    {
        b_block* loop = *header;
        while (loop->next)
        {
            loop = loop->next;
        }
        loop->next = current;
    }
}

void free_array(char** str)
{
    int i = 0;
    while (str[i])
    {
        free(str[i]);
        i++;
    }
    free(str);
}

void free_int_arr(int** arr)
{
    int i = 0;
    while (arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}

void free_list(b_block* head)
{
    b_block* current = head;
    b_block* next = NULL;
    while (current)
    {
        next = current->next;
        free(current->line);
        free(current);
        current = next;
    }
}

int find_the_min(int p1, int p2, int p3)
{
    if (p1 <= p2 && p1 <= p3)
    {
        return p1;
    }
    else if (p2 <= p1 && p2 <= p3)
    {
        return p2;
    }
    else
    {
        return p3;
    }
}

void inner_loop(int** arr, int length_line, int i)
{
    int j = 0;
    while (j < length_line)
    {
        if (arr[i][j] != 0)
        {
            if (i != 0 && j != 0)
            {
                if (arr[i - 1][j] && arr[i - 1][j - 1] && arr[i][j] &&
                    arr[i][j - 1])
                {
                    arr[i][j] += find_the_min(arr[i - 1][j], arr[i - 1][j - 1], arr[i][j - 1]);
                }
            }
        }
        j++;
    }
}

void modify_arr(int** arr, int length_line)
{
    int i = 0;
    while (arr[i])
    {
        inner_loop(arr, length_line, i);
        i++;
    }
}