#include "../h/search_process.h"

void print_list(b_block* head)
{
    b_block* list = head;
    while (list)
    {
        printf("%s\n", list->line);
        list = list->next;
    }
}

void map_to_digit(int* dest, char* map)
{
    for (int i = 0; i < my_strlen(map); i++)
    {
        if (map[i] != 'o')
        {
            dest[i] = 1;
        }
        else
        {
            dest[i] = 0;
        }
    }
}

int* finding_line(int index_max, int max_num)
{
    int* line_arr = calloc(sizeof(int), (max_num + 1));
    int ind = 0;
    int temp_max = max_num;
    temp_max--;
    while (temp_max >= 0)
    {
        line_arr[ind++] = index_max;
        temp_max--;
        index_max--;
    }
    return line_arr;
}

int* finding_column(int line_max, int max_num)
{
    int* line_arr = calloc(sizeof(int), (max_num + 1));
    int ind = 0;
    int temp_max = max_num;
    temp_max--;
    while (temp_max >= 0)
    {
        line_arr[ind++] = line_max;
        temp_max--;
        line_max--;
    }
    return line_arr;
}

int l_line_flag(square_data* map, int i)
{
    int line_flag = 0;
    for (int ind = 0; ind < map->max_num; ind++)
    {
        if (map->line_arr[ind] == i)
        {
            line_flag = 1;
        }
    }
    return line_flag;
}

int i_index_flag(square_data* map, int j)
{
    int index_flag = 0;
    for (int ind = 0; ind < map->max_num; ind++)
    {
        if (map->index_arr[ind] == j)
        {
            index_flag = 1;
        }
    }
    return index_flag;
}

int checking_ind(square_data* map, int j, int i)
{
    int line_flag = l_line_flag(map, i);
    int index_flag = i_index_flag(map, j);
    if (line_flag == 1 && index_flag == 1)
    {
        return 1;
    }
    return 0;
}

void filling_with_xo(square_data* map, int ind, int length_line, int** arr,
                     char* line)
{
    int k = 0;
    while (k < length_line)
    {
        if (checking_ind(map, k, ind) == 1)
        {
            line[k] = 'x';
        }
        else if (arr[ind][k] == 0)
        {
            line[k] = 'o';
        }
        else
        {
            line[k] = '.';
        }
        k++;
    }
}

square_data beg_matching(int** arr, int length_line)
{
    square_data map;
    int i = 0;
    map.line_max = 0;
    map.index_max = 0;
    map.max_num = 0;
    while (arr[i])
    {
        int j = 0;
        while (j < length_line)
        {
            if (arr[i][j] > map.max_num)
            {
                map.max_num = arr[i][j];
                map.line_max = i;
                map.index_max = j;
            }
            j++;
        }
        i++;
    }
    return map;
}

void matching_square(int** arr, int length_line)
{
    square_data map = beg_matching(arr, length_line);
    map.line_arr = finding_column(map.line_max, map.max_num);
    map.index_arr = finding_line(map.index_max, map.max_num);

    b_block* head = NULL;
    int ind = 0;
    while (arr[ind])
    {
        char* line = (char*)calloc(sizeof(char), (length_line + 1));
        filling_with_xo(&map, ind, length_line, arr, line);
        add_list(&head, line, length_line);
        free(line);
        ind++;
    }
    print_list(head);
    free_list(head);
    free(map.index_arr);
    free(map.line_arr);
}