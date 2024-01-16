#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

#include "../../bsq/h/my_string_lib.h"

typedef struct map_informations
{
    int column;
    int line;
    int** arr;
} map_info;

void free_array(char** arr)
{
    int i = 0;
    while (arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}

void free_int_array(int** arr, int col)
{
    int i = 0;
    while (i < col)
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}

void print_list(map_info* current_map)
{
    int i = 0;
    while (i < current_map->column)
    {
        int j = 0;
        while (j < current_map->line)
        {
            printf("%d ", current_map->arr[i][j]); 
            j++;
        }
        printf("\n");
        i++;
    }
}

void convert_completed_map(map_info* current_map, char* first_line, int* indexes)
{
    char** finished_map = (char**)calloc(sizeof(char*), current_map->column + 3);
    finished_map[current_map->column + 2] = NULL;
    for (int i = 0; i < current_map->column + 2; i++)
    {
        finished_map[i] = (char*)calloc(sizeof(char), current_map->line + 1);
    }
    my_strcpy(finished_map[0], first_line);
    int col = 1;
    int count = 0;

    for (int i = 0; i < current_map->column; i++)
    {
        for (int j = 0; j < current_map->line; j++)
        {
            if (current_map->arr[i][j] == 7777)
            {
                finished_map[col][j] = 'o';
                count++;
            }
            else if (current_map->arr[i][j])
            {
                finished_map[col][j] = ' ';
            }
            else
            {
                finished_map[col][j] = '*';
            }
        }
        col++;
    }

    if (count == 0)
    {
        char* ERROR = calloc(sizeof(char), 25);
        my_strcpy(ERROR, "Maze does not have path\n");
        write(1, ERROR, my_strlen(ERROR));
        free_array(finished_map);
        free(ERROR);
        return;
    }
    
    char* steps_counter = dec_to_char(count);
    finished_map[1][indexes[0]] = '1';
    finished_map[col - 1][indexes[1]] = '2';
    strcpy(finished_map[col], steps_counter);
    strcpy(&finished_map[col][my_strlen(steps_counter)], " STEPS");
    free(steps_counter);
    for (int i = 0; i < current_map->column + 2; i++)
    {
        printf("%s\n", finished_map[i]);
    }

    free_array(finished_map);
}

void map_to_digit(int* dest, char* map)
{
    for (int i = 0;i < my_strlen(map); i++)
    {
        if (map[i] == '*')
        {
            dest[i] = 0;
        }
        else if (map[i] == ' ')
        {
            dest[i] = 1;
        }
        else 
        {
            dest[i] = 1;
        }
    }
}

int is_digit(char letter)
{
    if (letter >= '0' && letter <= '9')
    {
        return 1;
    }
    return 0;
}

int* start_end_points(map_info* current_map)
{
    int* start_end = calloc(sizeof(int), 3);
    int start_point;
    int end_point;
    for (int i = 0; i < current_map->line; i++)
    {
        if (current_map->arr[0][i] == 1)
        {
            start_point = i;
        }
    }

    for (int i = 0; i < current_map->line; i++)
    {
        if (current_map->arr[current_map->column - 1][i] == 1 || current_map->arr[current_map->column - 1][i] == 2)
        {
            end_point = i;
        }
    }

    start_end[0] = start_point;
    start_end[1] = end_point ;

    return start_end;
}

void adding_value(int** arr, int i, int j, int col)
{
    int index = arr[i][j];
    if (arr[i][j + 1] == 1 && i != col - 1)
    {
        arr[i][j + 1] += index;
    }
    if (arr[i][j - 1] == 1)
    {
        arr[i][j - 1] += index;
    }
    if (arr[i + 1][j] == 1)
    {
        arr[i + 1][j] += index;
    }
    if (arr[i - 1][j] == 1 && i != 1)
    {
        arr[i - 1][j] += index;
    }
}

int* drawing_path(map_info* current_map, int i, int j, int* indexes)
{
    if (i > 0 && current_map->arr[i - 1][j] && current_map->arr[i - 1][j] == (current_map->arr[i][j] - 1))
    {
        current_map->arr[i][j] = 7777;
        indexes[0] = i - 1;
        indexes[1] = j;
        return indexes;
    }
    else if (j > 0 && current_map->arr[i][j - 1] && current_map->arr[i][j - 1] == (current_map->arr[i][j] - 1))
    {
        current_map->arr[i][j] = 7777;
        indexes[0] = i;
        indexes[1] = j - 1;
        return indexes;
    }
    else if (i < (current_map->line - 1) && current_map->arr[i + 1][j] && current_map->arr[i + 1][j] == (current_map->arr[i][j] - 1))
    {
        current_map->arr[i][j] = 7777;
        indexes[0] = i + 1;
        indexes[1] = j;
        return indexes;
    }
    else if (j < (current_map->line - 1) && current_map->arr[i][j + 1] && current_map->arr[i][j + 1] == (current_map->arr[i][j] - 1))
    {
        current_map->arr[i][j] = 7777;
        indexes[0] = i;
        indexes[1] = j + 1;
        return indexes;
    }
    indexes[0] = 99999;
    indexes[1] = 11111;
    return indexes;
}

int matching_shortest_path( map_info* current_map ,int end_point)
{
    int index = current_map->arr[current_map->column - 2][end_point];
    int* indexes = calloc(sizeof(int), 3);
    indexes[0] = current_map->line - 2;
    indexes[1] = end_point;

    while (index != 1)
    {
        indexes = drawing_path(current_map, indexes[0], indexes[1], indexes);
        if (indexes[0] == 99999 && indexes[1] == 11111)
        {
            char* ERROR = calloc(sizeof(char), 11);
            my_strcpy(ERROR, "MAP ERROR\n");
            write(2, ERROR, 10);
            free(indexes);
            free(ERROR);
            return 1;
        }
        index = current_map->arr[indexes[0]][indexes[1]];
    }
    current_map->arr[indexes[0]][indexes[1]] = 1;
    current_map->arr[current_map->column - 1][end_point] = 2;
    free(indexes);
    return 0;
}

int matching_path(map_info* current_map)
{
    int* start_end = start_end_points(current_map);
    current_map->arr[1][start_end[0]]++;
    
    for (int i = 2; i <= current_map->line * 2; i++)
    {
        for (int j = 1; j < current_map->column - 1; j++)
        {
            for (int k = 1; k < current_map->column - 1; k++)
            {
                if (current_map->arr[j][k] == i)
                {
                    adding_value(current_map->arr, j, k, current_map->column);
                }
            }
        }
    }
    if (matching_shortest_path(current_map, start_end[1]) == 1)
    {
        free(start_end);
        return 1;
    }
    free(start_end);
    return 0;
}   

int* find_line_col(char* first_line)
{
    int* line_col = (int*)calloc(sizeof(int), 3);
    char** numbers = (char**)calloc(sizeof(char*), 3);
    numbers[0] = (char*)calloc(sizeof(char), 5);
    numbers[1] = (char*)calloc(sizeof(char), 5);
    int i = 0;
    int ind = 0;
    int str_ind = 0;
    
    while (str_ind < 3)
    {
        if (is_digit(first_line[i]) == 1)
        {
            numbers[str_ind][ind] = first_line[i];
            ind++;
        }
        else
        {
            str_ind++;
            ind = 0;
        }
        i++;
    }

    line_col[0] = char_to_dec(numbers[0]);
    line_col[1] = char_to_dec(numbers[1]);

    free_array(numbers);
    return line_col;
}

void read_from_file(char* map)
{
    struct stat fs;
    stat(map, &fs);
    if(fs.st_size == 0)
    {
        write(2, "MAP ERROR\n", 10);
        return;
    }
    else
    {
        int fd = open(map, O_RDONLY);
        char* actual_map = calloc(sizeof(char), (fs.st_size + 1));
        read(fd, actual_map, fs.st_size);
        close(fd);
        char** str2 = split(actual_map,'\n');
        map_info current_map;
        int* arr = find_line_col(str2[0]);
        current_map.line = arr[1];
        current_map.column = arr[0];
        current_map.arr = calloc(sizeof(int*), arr[1]);
        int i = 0;
        int map_ind = 1;
        while (i < arr[1])
        {
            current_map.arr[i] = calloc(sizeof(int), arr[1] + 1);
            map_to_digit(current_map.arr[i], str2[map_ind++]);
            i++;
        }
        if (matching_path(&current_map) == 1)
        {
            free_array(str2);
            free(map);
            free_int_array(current_map.arr, arr[1]);
            free(arr);
            return;
        }
        int* start_end_p = start_end_points(&current_map);
        convert_completed_map(&current_map, str2[0], start_end_p );
        free_array(str2);
        free(actual_map);
        free(arr);
        free(start_end_p);
    }
}

int main()
{
    read_from_file("mouse/mazes/maze.txt");
}